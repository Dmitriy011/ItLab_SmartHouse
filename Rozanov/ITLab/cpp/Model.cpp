#include "Model.h"

Model::Model(GLchar* cd)
{
	loadModel(cd);
}

void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);																			//���� �� ������ ������������� ����� � ����� �� ������� Draw.
	}
}

void Model::loadModel(string cd)																		//�������� ������ � ��������� ������ ����� � ������������ Assimp
{
	Assimp::Importer import;																			//��������� ��������� ������ Importer
	const aiScene* scene = import.ReadFile(cd, aiProcess_Triangulate | aiProcess_FlipUVs);				//����� ReadFile � ����������� ���� � ����� ������, � ������ ��������� (aiProcess_Triangulate - ��� ������� � ������ ��������, ������������ �� �� �������������, ���������� �������� �������������� ����� �������� � ����� �������������) (aiProcess_FlipUVs - ���������� �������� ���������� ��������� �� ��� oY ���, ��� ��� ����������)

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)						//�������� �� ������� �� ���� ��������� �� ������ �����, �������� ���� ����� � ����, ������������, ��� �� ��� ������ ��������
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}

	directory = cd.substr(0, cd.find_last_of('/'));

	processNode(scene->mRootNode, scene);
																
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	//���������� ��� ������������� ����� � ����(���� ����
	for (GLuint i = 0; i < node->mNumMeshes; i++)	
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];													//�������� ��������� �� ������ ������������� �����
		meshes.push_back(processMesh(mesh, scene));															//������ aiMesh ������������� � ������� ������ processMesh � ��������� ������ ������ Mesh � ����������� � ������ meshes
	}
	
	// ��������� �� �� ��������� ��� ������� ������� ����
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{	//��������� ���������, �������� � ���������� ���������
		Vertex vertex;
		vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		if (mesh->mTextureCoords[0])																		// ��������: ����� �������� ������� ���������� ���������
		{
			vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = vec2(0.0f);
		}
		
		vertices.push_back(vertex);
	}

	//��������� ��������: ������ �� ������ ������ � ���������� ��������, ����������� ��, ����� ������� � � ����� ������� ������������ ��� ���������
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//��������� ���������
	if (mesh->mMaterialIndex >= 0)																					//�������� �������� � �����
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");		//��������� ��������� �������� �/��� �������� ����������� ������. loadMaterialTextures �������� �� ���� ��������� ���������� ����, ��������� ���� � ������, ��������� � ���������� �������� ������� OpenGL, �������� ������ ���������� � ��������� ��������� Texture
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");	//��������� �������� ����������� ������
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)								//�������� �� ���� ��������� ���������� ����
	{
		//��������� ���� � ������
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			Texture texture;
			//���������� ��������
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str;
			//����
			textures.push_back(texture);
			// ������� �������� � ������ ��� �����������
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

unsigned int Model::TextureFromFile(const char* path, const string& directory, bool gamma)
{
		string filename = string(path);
		filename = directory + '/' + filename;

		GLuint textureID;
		glGenTextures(1, &textureID);																	//�������� ��������
		int width, height, nrComponents;
		cout << directory << "      " << filename << "         ";
		cout << filename.c_str() << endl;
		unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		
	
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SOIL_free_image_data(image);

		return textureID;
}
