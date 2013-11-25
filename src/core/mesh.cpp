#include "mesh.h"

Mesh::Mesh(Geometry* geometry_, Material* material_) {
	geometry = geometry_;
	material = material_;
        
	for(int i = 0; i < BUFFER_COUNT; ++i) {
		vbo[i] = 0;
	}
	
	glGenVertexArrays(1, &vao);
}

Mesh::Mesh() {
	geometry = NULL;
	material = NULL;

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

Geometry* Mesh::GetGeometry() {
	return geometry;
}

Material* Mesh::GetMaterial() {
	return material;
}

void Mesh::Draw() {
	glBindVertexArray(vao);
    
    if(geometry->HasIndices()) {
        glDrawElements(geometry->GetType(), geometry->GetIndicesCount(), GL_UNSIGNED_INT, 0);
    } else {
	    glDrawArrays(geometry->GetType(), 0, geometry->GetVerticesCount());
    }

	glBindVertexArray(0);
}

void Mesh::CreateBufferData() {
	glBindVertexArray(vao);
    glGenBuffers(1, &vbo[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, geometry->GetVerticesCount() * sizeof(glm::vec3), geometry->GetVertices(), GL_STATIC_DRAW);

    if(geometry->IsInterleaved()) {
        // unfortunately.. wavefront loader should really be improved to reorganize indices not to use interleaved
        glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
        glEnableVertexAttribArray(VERTEX_BUFFER);
        glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const GLvoid*)(3 * sizeof(float)));
        glEnableVertexAttribArray(NORMAL_BUFFER);
    } else {
        glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(VERTEX_BUFFER);
        glGenBuffers(1, &vbo[INDEX_BUFFER]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry->GetIndicesCount() * sizeof(unsigned int), geometry->GetIndices(), GL_STATIC_DRAW);
    }

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
