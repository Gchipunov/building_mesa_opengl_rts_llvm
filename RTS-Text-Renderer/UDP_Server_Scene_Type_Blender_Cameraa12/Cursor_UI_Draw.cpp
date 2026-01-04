
#include "Cursor_UI_Draw.h"

Cursor_UI_Draw::Cursor_UI_Draw(int screen_width, int screen_height) {
	m_CursorTexture = loadCursorTexture();

	Mouse_first_frame = false;
	Mouse_lastX = (float)screen_width / 2.0;
	Mouse_lastY = (float)screen_height / 2.0;

	m_screen_width = screen_width;
	m_screen_height = screen_height;

	MouseVirtualX = Mouse_lastX / (float)m_screen_width;

	MouseVirtualY = ((float)Mouse_lastY) / (float)m_screen_height;

}
Cursor_UI_Draw::~Cursor_UI_Draw() {}

void Cursor_UI_Draw::mouse_callback(GLFWwindow* window, float xposIn, float yposIn)
{
	//blendercamera->ProcessMouseMovement(xposIn, yposIn);
  //  camera2->ProcessMouseMovement(xposIn, yposIn);
//	float xpos = static_cast<float>(xposIn);
	//float ypos = static_cast<float>(yposIn);

	if (Mouse_first_frame)
	{
		Mouse_lastX = xposIn;
		Mouse_lastY = yposIn;
		Mouse_first_frame = false;
	}

	float xoffset = xposIn - Mouse_lastX;
	float yoffset = yposIn - Mouse_lastY; // reversed since y-coordinates go from bottom to top
	Mouse_lastX = xposIn;
	Mouse_lastY = yposIn;

	//00----------00
	//glm::vec2 mouse_vec2(Mouse_lastX, Mouse_lastY);
	//mouse_vec2 = glm::normalize(mouse_vec2);
	//00----------00
	//UpdateMousePos(Mouse_lastX, Mouse_lastY);
	//UpdateMousePos(mouse_vec2.x, mouse_vec2.y);


	float newMouseVirtualX = Mouse_lastX / (float)m_screen_width;
	float newMouseVirtualY = ((float)m_screen_height - Mouse_lastY) / (float)m_screen_height;

	// doesn't work because not , the actual class variables
/*
	if (newMouseVirtualX > 1.0f)
	{
		newMouseVirtualX = 1.0f;

	}
	if (newMouseVirtualY > 1.0f)
	{
		newMouseVirtualY = 1.0f;

	}
	if (newMouseVirtualX < -1.0f)
	{
		newMouseVirtualX = -1.0f;

	}
	if (newMouseVirtualY < -1.0f)
	{
		newMouseVirtualY = -1.0f;

	}
	*/

	//UpdateMousePos(Mouse_lastX / (float)m_screen_width, ((float)m_screen_height - Mouse_lastY) / (float)m_screen_height);
	UpdateMousePos(newMouseVirtualX, newMouseVirtualY);
	// float Mouse_PositionX += xoffset;
	// float Mouse_PositionY += yoffset;

	//MouseVirtualX = Mouse_lastX / (float)m_screen_width;

	//MouseVirtualY = ((float)m_screen_height - Mouse_lastY) / (float)m_screen_height;
	MouseVirtualX = newMouseVirtualX;

	MouseVirtualY = newMouseVirtualY;



	//	MouseVirtualY = ((float) Mouse_lastY) / (float)m_screen_height;
		/*
		if (MouseVirtualX > 1.0f)
		{
			MouseVirtualX = 1.0f;

		}
		if (MouseVirtualY > 1.0f)
		{
			MouseVirtualY = 1.0f;

		}
		if (MouseVirtualX < 0.0f)
		{
			MouseVirtualX = 0.0f;

		}
		if (MouseVirtualY < 0.0f)
		{
			MouseVirtualY = 0.0f;

		}*/


		//	printf("Cursor_UI_Draw mouse_callback MouseVirtualX: %f ,MouseVirtualY: %f\n\n", MouseVirtualX, MouseVirtualY);

}


GLuint loadCursorTexture()
{
	// You'll need an image loading library like SOIL, stb_image, etc.
	int width, height, channels;
	int desired_no_channels = 4;

	// unsigned char* image = stbi_load("path/to/cursor.png", &width, &height, &channels, STBI_RGBA);
	unsigned char* image = stbi_load("assets/Cursor_UI_Construction_64x64_Construction3.png", &width, &height, &channels, desired_no_channels);
	if (!image) {
		// Handle error
		return -1;
	}

	GLuint cursorTexture;
	glGenTextures(1, &cursorTexture);
	glBindTexture(GL_TEXTURE_2D, cursorTexture);
	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);


	return cursorTexture;
}

extern std::vector<float> mainVertices;
extern GLuint VAO;
extern GLuint VBO;

int iMouseIndex = 0;
float MouseWidth = 64.0f;
float MouseHeight = 64.0f;


// Assuming your mainVertices vector is a vector of floats.
// This is a simplified representation.
void push_vertex(std::vector<float>& vertices, float x, float y, float z, float u, float v, float vvtype) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(u);
	vertices.push_back(v);
	vertices.push_back(vvtype);
}


int AddCursorPlane(float x, float y, float z, float width, float height)
{
	float vvtype = 77.0f;

	//float divideHalf = 2.0f;
	float divideHalf = 4.0f;

	float halfWidth = width / divideHalf;
	float halfHeight = height / divideHalf;

	float v0x = x - halfWidth;
	float v1x = x + halfWidth;

	float v0y = y - halfHeight;
	float v1y = y + halfHeight;

	iMouseIndex = mainVertices.size();
	MouseWidth = width;
	MouseHeight = height;
	/*
	mainVertices.push_back(v1x); mainVertices.push_back(v0y); mainVertices.push_back(z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype);// bottom - left ); mainVertices.push_back( 0 (bottom-left)
	mainVertices.push_back(v1x); mainVertices.push_back(v1y); mainVertices.push_back(z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype);// bottom - right ); mainVertices.push_back( 1 (bottom-right)
	mainVertices.push_back(v0x); mainVertices.push_back(v1y); mainVertices.push_back(z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype);// top -right ); mainVertices.push_back( 2 (top-right)
	mainVertices.push_back(v1x); mainVertices.push_back(v0y); mainVertices.push_back(z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype);// bottom - left ); mainVertices.push_back( 0 (bottom-left)
	mainVertices.push_back(v0x); mainVertices.push_back(v1y); mainVertices.push_back(z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype);// top -right ); mainVertices.push_back( 2 (top-right)
	mainVertices.push_back(v0x); mainVertices.push_back(v0y); mainVertices.push_back(z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype);// top - left  ); mainVertices.push_back( 3 (top-left)
	*/


	// The original un-rotated texture coordinates for a quad
	// (bottom-left, bottom-right, top-right, top-left)
	// Quad 1: bottom-left, bottom-right, top-right
	// Quad 2: bottom-left, top-right, top-left

	// Original, un-rotated UVs (for reference):
	// bottom-left: (0.0f, 0.0f)
	// bottom-right: (1.0f, 0.0f)
	// top-right: (1.0f, 1.0f)
	// top-left: (0.0f, 1.0f)

	// Rotating 90 degrees clockwise
	// A 90-degree clockwise rotation of UVs maps:
	// (u, v) -> (1-v, u)
	//
	// Original UV -> Rotated UV
	// (0.0, 0.0) -> (1-0.0, 0.0) = (1.0, 0.0)  // original bottom-left becomes rotated bottom-right
	// (1.0, 0.0) -> (1-0.0, 1.0) = (1.0, 1.0)  // original bottom-right becomes rotated top-right
	// (1.0, 1.0) -> (1-1.0, 1.0) = (0.0, 1.0)  // original top-right becomes rotated top-left
	// (0.0, 1.0) -> (1-1.0, 0.0) = (0.0, 0.0)  // original top-left becomes rotated bottom-left

	// Let's implement the rotation directly by re-mapping the original UVs.
	// We will use the original vertex positions, but apply the rotated UVs.
	// The key is to match the new UVs to the correct vertex corner.

	// Vertex 0 (original bottom-left): (v1x, v0y, z) -> New UVs are the old bottom-left, rotated: (1.0, 0.0)
	// This is the bottom-left vertex. The UV that was at the bottom-left corner (0,0) now maps to (1.0, 0.0)
	// But since the texture itself is rotated, the new "bottom-left" point on the rotated texture is what was originally the "top-left" point.
	// Let's re-think the logic from the perspective of the texture.

	// Rotating the texture 90 degrees clockwise means:
	// - The new bottom-left corner of the texture is the old bottom-left (0.0f, 0.0f)
	//   -> This isn't a simple mapping. Let's work with the corner names.

	// Original corner UVs:
	// A: bottom-left (0, 0)
	// B: bottom-right (1, 0)
	// C: top-right (1, 1)
	// D: top-left (0, 1)

	// After 90-degree clockwise rotation, the new mapping is:
	// New bottom-left is old D: (0, 1)
	// New bottom-right is old A: (0, 0)
	// New top-right is old B: (1, 0)
	// New top-left is old C: (1, 1)

	// Let's apply this to your original vertex creation:
	// Note: The comments `(bottom - left)`, etc. refer to the screen position of the vertex.
	// The code `mainVertices.push_back(0.0f); mainVertices.push_back(0.0f);` refers to the original texture UVs.

	// Quad 1:
	// Vertex 1: Original bottom-left screen position. Should get the new bottom-left UVs.
	// push_vertex(mainVertices, v1x, v0y, z, 0.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
////	mainVertices.push_back(0); // Pushing vertex index for clarity

	// Vertex 2: Original bottom-right screen position. Should get the new bottom-right UVs.
//	push_vertex(mainVertices, v1x, v1y, z, 0.0f, 0.0f, vvtype); // bottom-right screen position, new bottom-right UVs (from old bottom-left)
////	mainVertices.push_back(1);

	// Vertex 3: Original top-right screen position. Should get the new top-right UVs.
//	push_vertex(mainVertices, v0x, v1y, z, 1.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
////	mainVertices.push_back(2);

	// Quad 2:
	// Vertex 4: Original bottom-left screen position. Should get the new bottom-left UVs.
//	push_vertex(mainVertices, v1x, v0y, z, 0.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
////	mainVertices.push_back(0);

	// Vertex 5: Original top-right screen position. Should get the new top-right UVs.
//	push_vertex(mainVertices, v0x, v1y, z, 1.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
////	mainVertices.push_back(2);

	// Vertex 6: Original top-left screen position. Should get the new top-left UVs.
//	push_vertex(mainVertices, v0x, v0y, z, 1.0f, 1.0f, vvtype); // top-left screen position, new top-left UVs (from old top-right)
////	mainVertices.push_back(3);

	// --- Printing the result for verification ---
//	std::cout << "Vertices with 90-degree clockwise rotated UVs:" << std::endl;
//	for (size_t i = 0; i < mainVertices.size(); i += 7) { // 6 vertex components + 1 index
//		std::cout << "Vertex " << mainVertices[i + 6] << ": ("
//			<< mainVertices[i] << ", " << mainVertices[i + 1] << ", " << mainVertices[i + 2]
//			<< ") | UVs: (" << mainVertices[i + 3] << ", " << mainVertices[i + 4]
//			<< ") | Type: " << mainVertices[i + 5] << std::endl;
//	}

		// Quad 1:
	// Vertex 1: Original bottom-left screen position. Should get the new bottom-left UVs.
	push_vertex(mainVertices, v1x, v0y, z, 1.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
	////	mainVertices.push_back(0); // Pushing vertex index for clarity

		// Vertex 2: Original bottom-right screen position. Should get the new bottom-right UVs.
	push_vertex(mainVertices, v1x, v1y, z, 1.0f, 0.0f, vvtype); // bottom-right screen position, new bottom-right UVs (from old bottom-left)
	////	mainVertices.push_back(1);

		// Vertex 3: Original top-right screen position. Should get the new top-right UVs.
	push_vertex(mainVertices, v0x, v1y, z, 0.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
	////	mainVertices.push_back(2);

		// Quad 2:
		// Vertex 4: Original bottom-left screen position. Should get the new bottom-left UVs.
	push_vertex(mainVertices, v1x, v0y, z, 1.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
	////	mainVertices.push_back(0);

		// Vertex 5: Original top-right screen position. Should get the new top-right UVs.
	push_vertex(mainVertices, v0x, v1y, z, 0.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
	////	mainVertices.push_back(2);

		// Vertex 6: Original top-left screen position. Should get the new top-left UVs.
	push_vertex(mainVertices, v0x, v0y, z, 0.0f, 1.0f, vvtype); // top-left screen position, new top-left UVs (from old top-right)
	////	mainVertices.push_back(3);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data() );
	GLenum err = glGetError(); if (err != GL_NO_ERROR) {
		printf("OpenGL Error: %x\n", err);
		exit(7);
	}

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return 6;

}

void UpdateMousePos(float x, float y)
{

	float vvtype = 77.0f;

	float halfWidth = MouseWidth / 2.0f;
	float halfHeight = MouseHeight / 2.0f;

	float v0x = x - halfWidth;
	float v1x = x + halfWidth;

	float v0y = y - halfHeight;
	float v1y = y + halfHeight;

	//iMouseIndex = mainVertices.size();
	//MouseWidth = width;
	//MouseHeight = height;

//	mainVertices.push_back(v1x); mainVertices.push_back(v0y); mainVertices.push_back(z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype);// bottom - left ); mainVertices.push_back( 0 (bottom-left)
//	mainVertices.push_back(v1x); mainVertices.push_back(v1y); mainVertices.push_back(z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype);// bottom - right ); mainVertices.push_back( 1 (bottom-right)
//	mainVertices.push_back(v0x); mainVertices.push_back(v1y); mainVertices.push_back(z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype);// top -right ); mainVertices.push_back( 2 (top-right)
//	mainVertices.push_back(v1x); mainVertices.push_back(v0y); mainVertices.push_back(z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype);// bottom - left ); mainVertices.push_back( 0 (bottom-left)
//	mainVertices.push_back(v0x); mainVertices.push_back(v1y); mainVertices.push_back(z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype);// top -right ); mainVertices.push_back( 2 (top-right)
//	mainVertices.push_back(v0x); mainVertices.push_back(v0y); mainVertices.push_back(z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype);// top - left  ); mainVertices.push_back( 3 (top-left) 
	mainVertices[iMouseIndex] = v1x;     mainVertices[iMouseIndex + 1] = v0y; // mainVertices[iMouseIndex +2 ]  // mainVertices[iMouseIndex +3 ] //mainVertices[iMouseIndex +4 ] //mainVertices[iMouseIndex +5 ]  
	mainVertices[iMouseIndex + 6] = v1x;  mainVertices[iMouseIndex + 7] = v1y; // mainVertices[iMouseIndex +8 ]  // mainVertices[iMouseIndex +9 ] //mainVertices[iMouseIndex +10 ] //mainVertices[iMouseIndex +11 ]  
	mainVertices[iMouseIndex + 12] = v0x;  mainVertices[iMouseIndex + 13] = v1y; // mainVertices[iMouseIndex +14 ]  // mainVertices[iMouseIndex +15 ] //mainVertices[iMouseIndex +16 ] //mainVertices[iMouseIndex +17 ]  

	mainVertices[iMouseIndex + 18] = v1x;  mainVertices[iMouseIndex + 19] = v0y; // mainVertices[iMouseIndex +20 ]  // mainVertices[iMouseIndex +21 ] //mainVertices[iMouseIndex +22 ] //mainVertices[iMouseIndex +23 ]  
	mainVertices[iMouseIndex + 24] = v0x;  mainVertices[iMouseIndex + 25] = v1y; // mainVertices[iMouseIndex +26 ]  // mainVertices[iMouseIndex +27 ] //mainVertices[iMouseIndex +28 ] //mainVertices[iMouseIndex +29 ]  
	mainVertices[iMouseIndex + 30] = v0x;  mainVertices[iMouseIndex + 31] = v0y; // mainVertices[iMouseIndex +32 ]  // mainVertices[iMouseIndex +33 ] //mainVertices[iMouseIndex +34 ] //mainVertices[iMouseIndex +35 ]  



	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);
//adsd
//glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, iMouseIndex * sizeof(float), 36 * sizeof(float), mainVertices.data() + iMouseIndex);

	GLenum err = glGetError(); if (err != GL_NO_ERROR) {
		printf("OpenGL Error: %x\n", err);
		exit(7);
	}

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

int Add3DCursor()
{
	// vertices..


	return 0;

}

Cursor_UI_Draw* g_pCursor_UI_Draw = 0;
