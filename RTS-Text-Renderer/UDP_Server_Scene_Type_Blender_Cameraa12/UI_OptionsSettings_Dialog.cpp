
#include "UI_OptionsSettings_Dialog.h"


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
void push_vertex_optionssettingdialog(std::vector<float>& vertices, float x, float y, float z, float u, float v, float vvtype) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(u);
	vertices.push_back(v);
	vertices.push_back(vvtype);
}


UI_OptionsSettings_Dialog::UI_OptionsSettings_Dialog()
{
	iUI_OptionsSettings_Dialog_MainVertices_index = 0;
	m_iNumberOfDrawQuads = 7;

	StartXButton1 = 0.0f;
	EndXButton1 = 0.0f;
	StartYButton1 = 0.0f;
	EndYButton1 = 0.0f;
}
UI_OptionsSettings_Dialog::~UI_OptionsSettings_Dialog()
{


}

int UI_OptionsSettings_Dialog::CreateMainMenuQuads()
{
	float vvtype0 = 333.0f;

	float vvtype = 353.0f;


	int iStartUI_OptionsSettings_Dialog_Index = mainVertices.size();
	iUI_OptionsSettings_Dialog_MainVertices_index = mainVertices.size();


	float z2 = 0.3f;
	float fStartX2 = -0.55f; // 20% Percent from left side of the screen
	//	float fStartY = 0.20f +  (fIncreamentY * (float)i); // 20% Percent from left side of the screen
	float fStartY2 = -0.80f; // +(fIncreamentY * (float)i);

	float fEndX2 = 0.55f; // 20% Percent from left side of the screen
	float fEndY2 = 1.40f + fStartY2; // +(fIncreamentY * (float)i); // 20% Percent from left side of the screen

	//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index] = fEndX;     mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 1] = fStartY; // mainVertices[iMouseIndex +2 ]  // mainVertices[iMouseIndex +3 ] //mainVertices[iMouseIndex +4 ] //mainVertices[iMouseIndex +5 ]  
	//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 6] = fEndX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 7] = fEndY; // mainVertices[iMouseIndex +8 ]  // mainVertices[iMouseIndex +9 ] //mainVertices[iMouseIndex +10 ] //mainVertices[iMouseIndex +11 ]  
	//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 12] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 13] = fEndY; // mainVertices[iMouseIndex +14 ]  // mainVertices[iMouseIndex +15 ] //mainVertices[iMouseIndex +16 ] //mainVertices[iMouseIndex +17 ]  

	//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 18] = fEndX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 19] = fStartY; // mainVertices[iMouseIndex +20 ]  // mainVertices[iMouseIndex +21 ] //mainVertices[iMouseIndex +22 ] //mainVertices[iMouseIndex +23 ]  
	//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 24] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 25] = fEndY; // mainVertices[iMouseIndex +26 ]  // mainVertices[iMouseIndex +27 ] //mainVertices[iMouseIndex +28 ] //mainVertices[iMouseIndex +29 ]  
	//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 30] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 31] = fStartY; // mainVertices[iMouseIndex +32 ]  // mainVertices[iMouseIndex +33 ] //mainVertices[iMouseIndex +34 ] //mainVertices[iMouseIndex +35 ]  

		// Vertex 1: Original bottom-left screen position. Should get the new bottom-left UVs.
	push_vertex_optionssettingdialog(mainVertices, fEndX2, fStartY2, z2, 1.0f, 1.0f, vvtype0); // bottom-left screen position, new bottom-left UVs (from old top-left)
	////	mainVertices.push_back(0); // Pushing vertex index for clarity

		// Vertex 2: Original bottom-right screen position. Should get the new bottom-right UVs.
	push_vertex_optionssettingdialog(mainVertices, fEndX2, fEndY2, z2, 1.0f, 0.0f, vvtype0); // bottom-right screen position, new bottom-right UVs (from old bottom-left)
	////	mainVertices.push_back(1);

		// Vertex 3: Original top-right screen position. Should get the new top-right UVs.
	push_vertex_optionssettingdialog(mainVertices, fStartX2, fEndY2, z2, 0.0f, 0.0f, vvtype0); // top-right screen position, new top-right UVs (from old bottom-right)
	////	mainVertices.push_back(2);

		// Quad 2:
		// Vertex 4: Original bottom-left screen position. Should get the new bottom-left UVs.
	push_vertex_optionssettingdialog(mainVertices, fEndX2, fStartY2, z2, 1.0f, 1.0f, vvtype0); // bottom-left screen position, new bottom-left UVs (from old top-left)
	////	mainVertices.push_back(0);

		// Vertex 5: Original top-right screen position. Should get the new top-right UVs.
	push_vertex_optionssettingdialog(mainVertices, fStartX2, fEndY2, z2, 0.0f, 0.0f, vvtype0); // top-right screen position, new top-right UVs (from old bottom-right)
	////	mainVertices.push_back(2);

		// Vertex 6: Original top-left screen position. Should get the new top-left UVs.
	push_vertex_optionssettingdialog(mainVertices, fStartX2, fStartY2, z2, 0.0f, 1.0f, vvtype0); // top-left screen position, new top-left UVs (from old top-right)
	////	mainVertices.push_back(3);



	for (int i = 0; i < 6; i++)
	{
		float fIncreamentY = 0.20f;

		float fStartX = -0.50f; // 20% Percent from left side of the screen
		//	float fStartY = 0.20f +  (fIncreamentY * (float)i); // 20% Percent from left side of the screen
		//float fStartY = -0.50f + (fIncreamentY * (float)i);
		float fStartY = -0.70f + (fIncreamentY * (float)i);

		float fEndX = 0.50f; // 20% Percent from left side of the screen
		float fEndY = 0.16f + fStartY; // +(fIncreamentY * (float)i); // 20% Percent from left side of the screen

		printf("fStartX: %f, fEndX: %f, fStartY: %f, fEndY: %f\n", fStartX, fEndX, fStartY, fEndY);
		if (i == 0)
		{
			StartXButton1 = fStartX;
			EndXButton1 = fEndX;
			StartYButton1 = fStartY;
			EndYButton1 = fEndY;
		}


		float z = 0.2f;
		//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index] = fEndX;     mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 1] = fStartY; // mainVertices[iMouseIndex +2 ]  // mainVertices[iMouseIndex +3 ] //mainVertices[iMouseIndex +4 ] //mainVertices[iMouseIndex +5 ]  
		//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 6] = fEndX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 7] = fEndY; // mainVertices[iMouseIndex +8 ]  // mainVertices[iMouseIndex +9 ] //mainVertices[iMouseIndex +10 ] //mainVertices[iMouseIndex +11 ]  
		//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 12] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 13] = fEndY; // mainVertices[iMouseIndex +14 ]  // mainVertices[iMouseIndex +15 ] //mainVertices[iMouseIndex +16 ] //mainVertices[iMouseIndex +17 ]  

		//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 18] = fEndX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 19] = fStartY; // mainVertices[iMouseIndex +20 ]  // mainVertices[iMouseIndex +21 ] //mainVertices[iMouseIndex +22 ] //mainVertices[iMouseIndex +23 ]  
		//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 24] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 25] = fEndY; // mainVertices[iMouseIndex +26 ]  // mainVertices[iMouseIndex +27 ] //mainVertices[iMouseIndex +28 ] //mainVertices[iMouseIndex +29 ]  
		//	mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 30] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 31] = fStartY; // mainVertices[iMouseIndex +32 ]  // mainVertices[iMouseIndex +33 ] //mainVertices[iMouseIndex +34 ] //mainVertices[iMouseIndex +35 ]  

			// Vertex 1: Original bottom-left screen position. Should get the new bottom-left UVs.
		push_vertex_optionssettingdialog(mainVertices, fEndX, fStartY, z, 1.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
		////	mainVertices.push_back(0); // Pushing vertex index for clarity

			// Vertex 2: Original bottom-right screen position. Should get the new bottom-right UVs.
		push_vertex_optionssettingdialog(mainVertices, fEndX, fEndY, z, 1.0f, 0.0f, vvtype); // bottom-right screen position, new bottom-right UVs (from old bottom-left)
		////	mainVertices.push_back(1);

			// Vertex 3: Original top-right screen position. Should get the new top-right UVs.
		push_vertex_optionssettingdialog(mainVertices, fStartX, fEndY, z, 0.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
		////	mainVertices.push_back(2);

			// Quad 2:
			// Vertex 4: Original bottom-left screen position. Should get the new bottom-left UVs.
		push_vertex_optionssettingdialog(mainVertices, fEndX, fStartY, z, 1.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
		////	mainVertices.push_back(0);

			// Vertex 5: Original top-right screen position. Should get the new top-right UVs.
		push_vertex_optionssettingdialog(mainVertices, fStartX, fEndY, z, 0.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
		////	mainVertices.push_back(2);

			// Vertex 6: Original top-left screen position. Should get the new top-left UVs.
		push_vertex_optionssettingdialog(mainVertices, fStartX, fStartY, z, 0.0f, 1.0f, vvtype); // top-left screen position, new top-left UVs (from old top-right)
		////	mainVertices.push_back(3);


	}

	// exit(0);


	/*

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data() );
	GLenum err = glGetError(); if (err != GL_NO_ERROR) {
		printf("OpenGL Error: %x\n", err);
		exit(16);
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
	*/
	return 6 * 4;

}

void UI_OptionsSettings_Dialog::UpdateMainMenu()
{
	float vvtype0 = 333.0f;

	float vvtype1 = 353.0f;

	if (g_pAnaGameState->GetSettingOptionsDialogState() == 1)
	{
		vvtype0 = 334.0f;
		vvtype1 = 354.0f;

	}
	float vvtype = vvtype1; // vvtype0 first back panel, I know I can set it to vvtype1, but for demo straction and
	// more important future code, we need vvtype to depend on index!!

	int  iNumAttributesQuad = 6 * 6;
	if (iUI_OptionsSettings_Dialog_MainVertices_index != 0)
	{
#define NUM_PANELS_AND_BUTTONS 7   // back panel and 6 buttons
		for (int i = 0; i < NUM_PANELS_AND_BUTTONS; i++)
		{

			if (i == 0)
			{

				vvtype = vvtype0;
			}
			else
			{
				vvtype = vvtype1;
			}
			//	float fIncreamentY = 0.20f;

			//	float fStartX = 0.20f; // 20% Percent from left side of the screen
			//	float fStartY = 0.20f + (fIncreamentY * (float)i); // 20% Percent from left side of the screen

			//	float fEndX = 0.80f; // 20% Percent from left side of the screen
			//	float fEndY = 0.10f + fStartY + (fIncreamentY * (float)i); // 20% Percent from left side of the screen
			int iIndexUpdate = iUI_OptionsSettings_Dialog_MainVertices_index + (i * iNumAttributesQuad);


			//	mainVertices[iMainMenuUI_MainVertices_index] = fEndX;     mainVertices[iMainMenuUI_MainVertices_index + 1] = fStartY; // mainVertices[iMouseIndex +2 ]  // mainVertices[iMouseIndex +3 ] //mainVertices[iMouseIndex +4 ] //mainVertices[iMouseIndex +5 ]  
			//	mainVertices[iMainMenuUI_MainVertices_index + 6] = fEndX;  mainVertices[iMainMenuUI_MainVertices_index + 7] = fEndY; // mainVertices[iMouseIndex +8 ]  // mainVertices[iMouseIndex +9 ] //mainVertices[iMouseIndex +10 ] //mainVertices[iMouseIndex +11 ]  
			//	mainVertices[iMainMenuUI_MainVertices_index + 12] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 13] = fEndY; // mainVertices[iMouseIndex +14 ]  // mainVertices[iMouseIndex +15 ] //mainVertices[iMouseIndex +16 ] //mainVertices[iMouseIndex +17 ]  

			//	mainVertices[iMainMenuUI_MainVertices_index + 18] = fEndX;  mainVertices[iMainMenuUI_MainVertices_index + 19] = fStartY; // mainVertices[iMouseIndex +20 ]  // mainVertices[iMouseIndex +21 ] //mainVertices[iMouseIndex +22 ] //mainVertices[iMouseIndex +23 ]  
			//	mainVertices[iMainMenuUI_MainVertices_index + 24] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 25] = fEndY; // mainVertices[iMouseIndex +26 ]  // mainVertices[iMouseIndex +27 ] //mainVertices[iMouseIndex +28 ] //mainVertices[iMouseIndex +29 ]  
			//	mainVertices[iMainMenuUI_MainVertices_index + 30] = fStartX;  mainVertices[iMainMenuUI_MainVertices_index + 31] = fStartY; // mainVertices[iMouseIndex +32 ]  // mainVertices[iMouseIndex +33 ] //mainVertices[iMouseIndex +34 ] //mainVertices[iMouseIndex +35 ]  

			//	mainVertices[iIndexUpdate] = fEndX;     mainVertices[iIndexUpdate + 1] = fStartY; // mainVertices[iMouseIndex +2 ]  // mainVertices[iMouseIndex +3 ] //mainVertices[iMouseIndex +4 ] //mainVertices[iMouseIndex +5 ]  
			mainVertices[iIndexUpdate + 5] = vvtype;
			//	mainVertices[iIndexUpdate + 6] = fEndX;  mainVertices[iIndexUpdate + 7] = fEndY; // mainVertices[iMouseIndex +8 ]  // mainVertices[iMouseIndex +9 ] //mainVertices[iMouseIndex +10 ] //mainVertices[iMouseIndex +11 ]  
			mainVertices[iIndexUpdate + 11] = vvtype;
			//	mainVertices[iIndexUpdate + 12] = fStartX;  mainVertices[iIndexUpdate + 13] = fEndY; // mainVertices[iMouseIndex +14 ]  // mainVertices[iMouseIndex +15 ] //mainVertices[iMouseIndex +16 ] //mainVertices[iMouseIndex +17 ]  
			mainVertices[iIndexUpdate + 17] = vvtype;
			//	mainVertices[iIndexUpdate + 18] = fEndX;  mainVertices[iIndexUpdate + 19] = fStartY; // mainVertices[iMouseIndex +20 ]  // mainVertices[iMouseIndex +21 ] //mainVertices[iMouseIndex +22 ] //mainVertices[iMouseIndex +23 ]  
			mainVertices[iIndexUpdate + 23] = vvtype;
			//	mainVertices[iIndexUpdate + 24] = fStartX;  mainVertices[iIndexUpdate + 25] = fEndY; // mainVertices[iMouseIndex +26 ]  // mainVertices[iMouseIndex +27 ] //mainVertices[iMouseIndex +28 ] //mainVertices[iMouseIndex +29 ]  
			mainVertices[iIndexUpdate + 29] = vvtype;
			//	mainVertices[iIndexUpdate + 30] = fStartX;  mainVertices[iIndexUpdate + 31] = fStartY; // mainVertices[iMouseIndex +32 ]  // mainVertices[iMouseIndex +33 ] //mainVertices[iMouseIndex +34 ] //mainVertices[iMouseIndex +35 ]  
			mainVertices[iIndexUpdate + 35] = vvtype;

		}

	}
	/*
	if(iUI_OptionsSettings_Dialog_MainVertices_index != 0)
	{
	for (int i = 0; i < 4; i++)
	{
		float fIncreamentY = 0.20f;

		float fStartX = 0.20f; // 20% Percent from left side of the screen
		float fStartY = 0.20f + (fIncreamentY * (float)i); // 20% Percent from left side of the screen

		float fEndX = 0.80f; // 20% Percent from left side of the screen
		float fEndY = 0.10f + fStartY + (fIncreamentY * (float)i); // 20% Percent from left side of the screen


		mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index] = fEndX;     mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 1] = fStartY; // mainVertices[iMouseIndex +2 ]  // mainVertices[iMouseIndex +3 ] //mainVertices[iMouseIndex +4 ] //mainVertices[iMouseIndex +5 ]
		mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 6] = fEndX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 7] = fEndY; // mainVertices[iMouseIndex +8 ]  // mainVertices[iMouseIndex +9 ] //mainVertices[iMouseIndex +10 ] //mainVertices[iMouseIndex +11 ]
		mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 12] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 13] = fEndY; // mainVertices[iMouseIndex +14 ]  // mainVertices[iMouseIndex +15 ] //mainVertices[iMouseIndex +16 ] //mainVertices[iMouseIndex +17 ]

		mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 18] = fEndX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 19] = fStartY; // mainVertices[iMouseIndex +20 ]  // mainVertices[iMouseIndex +21 ] //mainVertices[iMouseIndex +22 ] //mainVertices[iMouseIndex +23 ]
		mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 24] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 25] = fEndY; // mainVertices[iMouseIndex +26 ]  // mainVertices[iMouseIndex +27 ] //mainVertices[iMouseIndex +28 ] //mainVertices[iMouseIndex +29 ]
		mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 30] = fStartX;  mainVertices[iUI_OptionsSettings_Dialog_MainVertices_index + 31] = fStartY; // mainVertices[iMouseIndex +32 ]  // mainVertices[iMouseIndex +33 ] //mainVertices[iMouseIndex +34 ] //mainVertices[iMouseIndex +35 ]



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


void UI_OptionsSettings_Dialog::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{

}
void UI_OptionsSettings_Dialog::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{


}


void UI_OptionsSettings_Dialog::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	// int g_mouse_button = button;
	// int g_mouse_action = action;
	// int g_mouse_mods = mods;



	if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		if (action == GLFW_PRESS) {
			//    camera->is_middle_button_pressed = true;
			 //   camera->is_shift_pressed = (mods & GLFW_MOD_SHIFT);
		}
		else if (action == GLFW_RELEASE) {
			//    camera->is_middle_button_pressed = false;
		}
	}





	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//  double xpos, ypos;
		  // Get the cursor position in screen coordinates
		//  glfwGetCursorPos(window, &xpos, &ypos);
		if (g_pCursor_UI_Draw && g_pAnaGameState)
		{

			printf("UI_OptionsSettings_Dialog::StartXButton1:  %f EndXButton1: %f \n", StartXButton1, EndXButton1);
			printf("UI_OptionsSettings_Dialog::StartYButton1:  %f EndYButton1: %f \n", StartYButton1, EndYButton1);

			if (g_pAnaGameState->GetSettingOptionsDialogState() == 1)
			{
				float mouse3x = g_pCursor_UI_Draw->MouseVirtualX;
				float mouse3y = g_pCursor_UI_Draw->MouseVirtualY;
				printf("UI_OptionsSettings_Dialog::mouse_button_callback: mouse3x: %f mouse3y: %f \n", mouse3x, mouse3y);
				printf("UI_OptionsSettings_Dialog:: if(g_pAnaGameState->GetSettingOptionsDialogState() == 1) \n");

				if (mouse3x > StartXButton1 && mouse3x < EndXButton1 && mouse3y > StartYButton1 && mouse3y < EndYButton1)
				{
					printf(" UI_OptionsSettings_Dialog:: g_pAnaGameState->SetSettingOptionsDialogState(0);\n");
					g_pAnaGameState->SetSettingOptionsDialogState(0);

				}
			}
		}

		// 1. Normalize device coordinates (NDC) from screen coordinates
	  //  float x = (2.0f * xpos) / g_Width - 1.0f;
	  //  float y = 1.0f - (2.0f * ypos) / g_Height;
	  //  float z = 1.0f;
	   // glm::vec3 ray_nds = glm::vec3(x, y, z);

	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {


	}


	if (button == GLFW_MOUSE_BUTTON_4 && action == GLFW_PRESS) {




	}


}

void UI_OptionsSettings_Dialog::TurnOffVSync()
{
	glfwSwapInterval(0); // Sets the swap interval to 0 (disabling V-Sync)

}
void UI_OptionsSettings_Dialog::TurnOnVSync()
{
	glfwSwapInterval(1); // Sets the swap interval to 0 (disabling V-Sync)

}

void UI_OptionsSettings_Dialog::TurnOnVSync_Ext()
{
	glfwSwapInterval(-1); // Swap Interval = −1: On supported drivers/extensions (EXT_swap_control_tear), this enables Adaptive V-Sync.
}

UI_OptionsSettings_Dialog* g_ANA_UI_OptionsSettings_Dialog;

