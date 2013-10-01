#include "mesh.h"

Mesh::Mesh(Geometry* geometry_, Material* material_) {
	geometry = geometry_;
	material = material_;
        
	for(int i = 0; i < BUFFER_COUNT; ++i) {
		vbo[i] = 0;
	}
	
	glGenVertexArrays(1, &vao);
}

Mesh::~Mesh(void) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(BUFFER_COUNT, vbo);

	delete material;
	delete geometry;
}

void Mesh::SetTexture(GLuint tex) {
	texture = tex;
}

Geometry* Mesh::GetGeometry() {
	return geometry;
}

Material* Mesh::GetMaterial() {
	return material;
}

void Mesh::Draw() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
    
    if(geometry->HasIndices()) {
        glDrawElements(geometry->GetType(), geometry->GetIndicesCount(), GL_UNSIGNED_INT, 0);
    } else {
	    glDrawArrays(geometry->GetType(), 0, geometry->GetVerticesCount());
    }

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Mesh* Mesh::Triangle(ShaderLibrary* shaderLibrary) {
    float size = 1.0f;

    float vertices[] = {
        -size,  size,  size,
        -size, -size,  size,
         size, -size,  size,
         size,  size,  size,
        -size,  size, -size,
        -size, -size, -size,
         size, -size, -size,
         size,  size, -size,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        3, 2, 7,
        2, 7, 6,
        6, 4, 7,
        6, 4, 5,
        0, 5, 4,
        0, 5, 1,
        0, 4, 3,
        3, 4, 7,
    };

    float UVs[] = {
        0, 1,
        0, 0,
        1, 0,
        1, 1,
    };

    Geometry* geometry = new Geometry(reinterpret_cast<glm::vec3*>(vertices), indices, 8, 10);
    //geometry->SetUVs(reinterpret_cast<glm::vec2*>(UVs));
	Material* material = new Material(shaderLibrary->GetShader("basic"));

	Mesh *mesh = new Mesh(geometry, material);
	mesh->CreateBufferData();

	return mesh;
}

void Mesh::CreateBufferData() {
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);

	// send data to opengl
	glBufferData(GL_ARRAY_BUFFER, geometry->GetVerticesCount() * sizeof(glm::vec3), geometry->GetVertices(), GL_STATIC_DRAW);

	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	if(geometry->HasTexCoords()) {
		glGenBuffers(1, &vbo[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXTURE_BUFFER]);

		glBufferData(GL_ARRAY_BUFFER, geometry->GetUVsCount() * sizeof(glm::vec2), geometry->GetUVs(), GL_STATIC_DRAW);

		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}
	if(geometry->HasColors()) {
        cout << "creation of colour buffer" << endl;
		glGenBuffers(1, &vbo[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[COLOUR_BUFFER]);

		glBufferData(GL_ARRAY_BUFFER, geometry->GetVerticesCount() * sizeof(glm::vec4), geometry->GetColours(), GL_STATIC_DRAW);

		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}
    if(geometry->HasIndices()) {
        cout << "creation of index buffer" << endl;
        glGenBuffers(1, &vbo[INDEX_BUFFER]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry->GetIndicesCount() * sizeof(unsigned int), geometry->GetIndices(), GL_STATIC_DRAW);
    }

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
