#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;

out vec2 TexCoord;
out float vvtype;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int iUniformsRenderType;

void main()
{
	vvtype = aTexCoord.z;

	if(vvtype > 76.5 && vvtype < 77.5)
	{
	// gl_Position = projection * view * model * vec4(aPos, 1.0f);
		gl_Position =  vec4(aPos, 1.0f);
	}
	else if(vvtype > 110.5 && vvtype < 111.5)
	{
		if(iUniformsRenderType == 1)
		{
		//	gl_Position = projection * view * model * vec4(aPos, 1.0f);
		gl_Position =  vec4(aPos, 1.0f);
		}
		else
		{
		gl_Position =  vec4(aPos, 1.0f);
		}
	}
	else if(vvtype > 221.5 && vvtype < 223.5) //222 = invisable, 223= visualiable in-game :: visiable and invisiable, help save instructions in shader
	{
		
		gl_Position =  vec4(aPos, 1.0f);
		
	}
	else if(vvtype > 332.5 && vvtype < 334.5) // visiable and invisiable, help save instructions in shader
	{
		
		gl_Position =  vec4(aPos, 1.0f);
		
	}

	else if(vvtype > 352.5 && vvtype < 354.5) // visiable and invisiable, help save instructions in shader
	{
		
		gl_Position =  vec4(aPos, 1.0f);
		
	}
	else if(vvtype >1019.5f &&  vvtype < 1027.5f)
	{
		gl_Position =  vec4(aPos, 1.0f);
	}

	else
	{
		gl_Position = projection * view * model * vec4(aPos, 1.0f);
	}

 TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}