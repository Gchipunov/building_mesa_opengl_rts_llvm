
#include "GameHUD_UI_Build_Button4.h"


extern std::vector<float> mainVertices;
extern GLuint VAO;
extern GLuint VBO;
extern int iNumVertexAttributes; // 6

#define NUM_CUBE_SIDES 6
#define NUM_QUAD_PLANE_VERTICES 6

#define NUMBER_OF_PLANES 3

// https://huggingface.co/spaces/spectral-labs/SGS-1

// add water            [ ]

// transform vehicle    [ ]

// scatter cubes        [ ]

//  terrian morph move  [ ]


// Assuming your mainVertices vector is a vector of floats.
// This is a simplified representation.
void push_vertex_gameui_button4(std::vector<float>& vertices, float x, float y, float z, float u, float v, float vvtype) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(u);
	vertices.push_back(v);
	vertices.push_back(vvtype);
}


GameHUD_UI_Build_Button4::GameHUD_UI_Build_Button4()
{
	iMainMenuUI_MainVertices_index = 0;

	SpriteID_Icon = 0;
	BuildPercentage = 0;
}
GameHUD_UI_Build_Button4::~GameHUD_UI_Build_Button4()
{


}

int GameHUD_UI_Build_Button4::CreateMainMenuQuads()
{
	float vvtype = 1020.0f;

	int iStartMainMenuUI_Index = mainVertices.size();
	iMainMenuUI_MainVertices_index = mainVertices.size();
	for (int i = 0; i < 1; i++) // for (int i = 0; i < 4; i++) make 4 quads on top of each other
	{
		float fIncreamentY = 0.20f;

		float fStartX = 0.72f; // 20% Percent from left side of the screen
		//	float fStartY = 0.20f +  (fIncreamentY * (float)i); // 20% Percent from left side of the screen
		float fStartY = 0.47 - (0.25f * 3.0f);//0.10f + (fIncreamentY * (float)i);

		float fEndX = 0.880f; // 20% Percent from left side of the screen
		float fEndY = 0.16f + fStartY; // +(fIncreamentY * (float)i); // 20% Percent from left side of the screen

		printf("fStartX: %f, fEndX: %f, fStartY: %f, fEndY: %f\n", fStartX, fEndX, fStartY, fEndY);

		// float fIncreamentY = 0.25f;

	//	float fStartX = 0.70f; // 20% Percent from left side of the screen
		//	float fStartY = 0.20f +  (fIncreamentY * (float)i); // 20% Percent from left side of the screen
	//	float fStartY = -0.80f + (fIncreamentY * (float)i);

	//	float fEndX = 0.90f; // 20% Percent from left side of the screen
	//	float fEndY = 0.20f + fStartY; // +(fIncreamentY * (float)i); // 20% Percent from left side of the screen



		float z = -0.01f;
		//	mainVertices[iMainMenuUI_MainVertices_index] = fEndX;     mainVertices[iMainMenuUI_MainVertices_index + 1] = fStartY; // mainVertices[iMouseIndex +2 ]  // mainVertices[iMouseIndex +3 ] //mainVertices[iMouseIndex +4 ] //mainVertices[iMouseIndex +5 ]  
		//	mainVertices[iMainMenuUI_MainVertices_index + 6] = fEndX;  mainVertices[iMainMenuUI_MainVertices_index + 7] = fEndY; // mainVertices[iMouseIndex +8 ]  // mainVertices[iMouseIndex +9 ] //mainVertices[iMouseIndex +10 ] //mainVertices[iMouseIndex +11 ]  
		//	mainVertices[iMainMenuUI_MainVertices_index + 12] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 13] = fEndY; // mainVertices[iMouseIndex +14 ]  // mainVertices[iMouseIndex +15 ] //mainVertices[iMouseIndex +16 ] //mainVertices[iMouseIndex +17 ]  

		//	mainVertices[iMainMenuUI_MainVertices_index + 18] = fEndX;  mainVertices[iMainMenuUI_MainVertices_index + 19] = fStartY; // mainVertices[iMouseIndex +20 ]  // mainVertices[iMouseIndex +21 ] //mainVertices[iMouseIndex +22 ] //mainVertices[iMouseIndex +23 ]  
		//	mainVertices[iMainMenuUI_MainVertices_index + 24] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 25] = fEndY; // mainVertices[iMouseIndex +26 ]  // mainVertices[iMouseIndex +27 ] //mainVertices[iMouseIndex +28 ] //mainVertices[iMouseIndex +29 ]  
		//	mainVertices[iMainMenuUI_MainVertices_index + 30] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 31] = fStartY; // mainVertices[iMouseIndex +32 ]  // mainVertices[iMouseIndex +33 ] //mainVertices[iMouseIndex +34 ] //mainVertices[iMouseIndex +35 ]  

			// Vertex 1: Original bottom-left screen position. Should get the new bottom-left UVs.
		push_vertex_gameui_button4(mainVertices, fEndX, fStartY, z, 1.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
		////	mainVertices.push_back(0); // Pushing vertex index for clarity

			// Vertex 2: Original bottom-right screen position. Should get the new bottom-right UVs.
		push_vertex_gameui_button4(mainVertices, fEndX, fEndY, z, 1.0f, 0.0f, vvtype); // bottom-right screen position, new bottom-right UVs (from old bottom-left)
		////	mainVertices.push_back(1);

			// Vertex 3: Original top-right screen position. Should get the new top-right UVs.
		push_vertex_gameui_button4(mainVertices, fStartX, fEndY, z, 0.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
		////	mainVertices.push_back(2);

			// Quad 2:
			// Vertex 4: Original bottom-left screen position. Should get the new bottom-left UVs.
		push_vertex_gameui_button4(mainVertices, fEndX, fStartY, z, 1.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
		////	mainVertices.push_back(0);

			// Vertex 5: Original top-right screen position. Should get the new top-right UVs.
		push_vertex_gameui_button4(mainVertices, fStartX, fEndY, z, 0.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
		////	mainVertices.push_back(2);

			// Vertex 6: Original top-left screen position. Should get the new top-left UVs.
		push_vertex_gameui_button4(mainVertices, fStartX, fStartY, z, 0.0f, 1.0f, vvtype); // top-left screen position, new top-left UVs (from old top-right)
		////	mainVertices.push_back(3);


	}

	// exit(0);



	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data() );
	GLenum err = glGetError(); if (err != GL_NO_ERROR) {
		printf("OpenGL Error: %x\n", err);
		exit(116);
	}

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//return 6;

	return 6 * 4;

}

void GameHUD_UI_Build_Button4::UpdateMainMenu()
{
	/*
	if(iMainMenuUI_MainVertices_index != 0)
	{
	for (int i = 0; i < 4; i++)
	{
		float fIncreamentY = 0.20f;

		float fStartX = 0.20f; // 20% Percent from left side of the screen
		float fStartY = 0.20f + (fIncreamentY * (float)i); // 20% Percent from left side of the screen

		float fEndX = 0.80f; // 20% Percent from left side of the screen
		float fEndY = 0.10f + fStartY + (fIncreamentY * (float)i); // 20% Percent from left side of the screen


		mainVertices[iMainMenuUI_MainVertices_index] = fEndX;     mainVertices[iMainMenuUI_MainVertices_index + 1] = fStartY; // mainVertices[iMouseIndex +2 ]  // mainVertices[iMouseIndex +3 ] //mainVertices[iMouseIndex +4 ] //mainVertices[iMouseIndex +5 ]
		mainVertices[iMainMenuUI_MainVertices_index + 6] = fEndX;  mainVertices[iMainMenuUI_MainVertices_index + 7] = fEndY; // mainVertices[iMouseIndex +8 ]  // mainVertices[iMouseIndex +9 ] //mainVertices[iMouseIndex +10 ] //mainVertices[iMouseIndex +11 ]
		mainVertices[iMainMenuUI_MainVertices_index + 12] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 13] = fEndY; // mainVertices[iMouseIndex +14 ]  // mainVertices[iMouseIndex +15 ] //mainVertices[iMouseIndex +16 ] //mainVertices[iMouseIndex +17 ]

		mainVertices[iMainMenuUI_MainVertices_index + 18] = fEndX;  mainVertices[iMainMenuUI_MainVertices_index + 19] = fStartY; // mainVertices[iMouseIndex +20 ]  // mainVertices[iMouseIndex +21 ] //mainVertices[iMouseIndex +22 ] //mainVertices[iMouseIndex +23 ]
		mainVertices[iMainMenuUI_MainVertices_index + 24] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 25] = fEndY; // mainVertices[iMouseIndex +26 ]  // mainVertices[iMouseIndex +27 ] //mainVertices[iMouseIndex +28 ] //mainVertices[iMouseIndex +29 ]
		mainVertices[iMainMenuUI_MainVertices_index + 30] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 31] = fStartY; // mainVertices[iMouseIndex +32 ]  // mainVertices[iMouseIndex +33 ] //mainVertices[iMouseIndex +34 ] //mainVertices[iMouseIndex +35 ]



	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data() );
	GLenum err = glGetError(); if (err != GL_NO_ERROR) {
		printf("OpenGL Error: %x\n", err);
		exit(17);
	}

	// position attribute
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
// glEnableVertexAttribArray(0);
	// texture coord attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	}
	*/
}


void GameHUD_UI_Build_Button4::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{

}
void GameHUD_UI_Build_Button4::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{


}




GameHUD_UI_Build_Button4* g_ANA_GameHUD_UI_Build_Button4;

