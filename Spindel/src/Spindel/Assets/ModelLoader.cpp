#include "sppch.h"
#include "ModelLoader.h"

namespace Spindel
{
	ModelLoader::ModelLoader(Cache& cache)
		: Loader{cache, Type::staticMesh}
	{
	}
	bool ModelLoader::loadAsset(Bundle& bundle, const std::string& name, const std::string& filename, bool mipmaps)
	{
        m_Bundle = &bundle;
        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            SP_WARN("ERROR::ASSIMP:: {0}", importer.GetErrorString());
            return false;
        }
        // retrieve the directory path of the filepath
        m_Directory = filename.substr(0, filename.find_last_of('/')) + "/";
        //m_Name = filename.substr(filename.find_last_of('/') + 1, filename.find_last_of('.'));

        // process ASSIMP's root node recursively
        ProcessNode(scene->mRootNode, scene);
		return true;
	}

    void ModelLoader::LoadModel(const std::string& path)
    {

    }

    void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene)
    {
        // process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Bundle->setMesh(std::string(mesh->mName.C_Str()), ProcessMesh(mesh, scene));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Ref<Mesh> ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture2D>> textures;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        std::vector<Ref<Texture2D>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Ref<Texture2D>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Ref<Texture2D>> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Ref<Texture2D>> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        Ref<VertexArray> va = VertexArray::Create();
        Ref<VertexBuffer> vb = VertexBuffer::Create(vertices, vertices.size());

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float3, "a_Normal" },
            { ShaderDataType::Float2, "a_Texcoords" },
            { ShaderDataType::Float3, "a_Tangent" },
            { ShaderDataType::Float3, "a_Bitangent" }
        };
        vb->SetLayout(layout);
        va->AddVertexBuffers(vb);


        Ref<IndexBuffer> ib = IndexBuffer::Create(indices);
        va->AddIndexBuffer(ib);

        Ref<Mesh> m = Mesh::Create(va, vb, ib, textures);
        return m;
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
     // the required info is returned as a Texture struct.
    std::vector<Ref<Texture2D>> ModelLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
    {
        std::vector<Ref<Texture2D>> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;

            std::string s = std::string(str.C_Str());
            s = s.substr(s.find_last_of('/') + 1, s.back());
            Ref<Texture2D> temp = m_Bundle->getTexture(s.c_str());
            if (temp != nullptr)
            {
                textures.push_back(temp);
                skip = true;
                break;
            }
          
            // if texture hasn't been loaded already, load it
            if (!skip)
            {
                std::string filepath = m_Directory.c_str() + std::string(str.C_Str());
                m_Bundle->loadAsset(Type::image, s, filepath);
                Ref<Texture2D> texture = m_Bundle->getTexture(s.c_str());
                textures.push_back(texture);
            }
        }
        return textures;
    };
}