#include "opengl.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
float lastx, lasty, lastz; bool f; int cnt = 20;
Camera camera(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1, 0));
#pragma region data 
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
#pragma endregion
#pragma region function
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!f) { f = 1; lastx = xpos, lasty = ypos; return; }
	float daltax = xpos - lastx, daltay = ypos - lasty;
	lastx = xpos, lasty = ypos;
	camera.ProcessMouseMovement(daltax, daltay);
}
uint LoadImage(const char* name, int texSlot)
{
	uint texBuffer;
	glGenTextures(1, &texBuffer);
	glActiveTexture(GL_TEXTURE0 + texSlot);
	glBindTexture(GL_TEXTURE_2D, texBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(name, &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return texBuffer;
}
void SetUniformMat4(Shader* testShader, const char* name, mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(testShader->ID, name), 1, GL_FALSE, value_ptr(mat));
}
void SetUniformVec2(Shader* testShader, const char* name, vec2 vector)
{
	glUniform2f(glGetUniformLocation(testShader->ID, name), vector.x, vector.y);
}
void SetUniformVec3(Shader* testShader, const char* name, vec3 vector)
{
	glUniform3f(glGetUniformLocation(testShader->ID, name), vector.x, vector.y, vector.z);
}
void SetUniform1f(Shader* testShader, const char* name, float f)
{
	glUniform1f(glGetUniformLocation(testShader->ID, name), f);
}
void SetUniform1i(Shader* testShader, const char* name, int slot)
{
	glUniform1i(glGetUniformLocation(testShader->ID, name), slot);
}
#pragma endregion
int main()
{
    #pragma region init
	glfwInit(); stbi_set_flip_vertically_on_load(true);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(800, 600, "test", GL_FALSE, GL_FALSE);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glViewport(0, 0, 800, 600); 
	glEnable(GL_DEPTH_TEST);
	#pragma endregion
    #pragma region load shader, material, light
	Shader* testShader = new Shader("VertexPath.vert", "FragmentPath.frag");
	Material* material = new Material(testShader, { 1,1,1 }, LoadImage("container.png", 0), LoadImage("container_specular.png", 1), 64);
	DirectionalLight* light = new DirectionalLight({ 1, 1, -1 }, { 0,0,0 });
#pragma endregion
	#pragma region load VAO, VBO
	uint VAO, VBO, EBO; glewExperimental = GL_TRUE; glewInit();
	glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
	glGenBuffers(1, &VBO); glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	#pragma endregion

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		mat4 model(1), view(1), projection(1);
		model = rotate(model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));
		view = camera.GetViewMatrix();
		projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		
		testShader->use(); 
		SetUniformMat4(testShader, "model", model);
		SetUniformMat4(testShader, "view", view);
		SetUniformMat4(testShader, "projection", projection);
		SetUniformVec3(testShader, "objColor", { 1,1,1 });
		SetUniformVec3(testShader, "ambientColor", { 0.1,0.1,0.1 });
		SetUniformVec3(testShader, "cameraPos", camera.position);
		SetUniformVec3(testShader,"material.ambient",material->ambient);
		SetUniform1i(testShader, "material.diffuse", 0);
		SetUniform1i(testShader, "material.specular", 1);
		SetUniform1f(testShader, "material.shininess", material->shininess);
		SetUniformVec3(testShader, "dLight.pos", light->position);
		SetUniformVec3(testShader, "dLight.dir", light->direction);
		SetUniformVec3(testShader, "dLight.color", light->color);
		//SetUniformVec3(testShader, "attenuation", light->attenuation);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
		#pragma region direction control
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (cnt) cnt--;
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			cnt = 20; float deep;
			glReadPixels(lastx, lasty, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &deep);
			vec3 objectPos = unProject(vec3(lastx, lasty, deep), model, projection, vec4(0, 0, 800, 600));
			printf("%.2lf %.2lf %.2lf\n", objectPos.x, objectPos.y, objectPos.z);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.position += vec3(0.05) * normalize(camera.forward);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.position -= vec3(0.05) * normalize(camera.right);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.position -= vec3(0.05) * normalize(camera.forward);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.position += vec3(0.05) * normalize(camera.right);
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			camera.position += vec3(0.05) * normalize(camera.up);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			camera.position -= vec3(0.05) * normalize(camera.up);
		}
		#pragma endregion
	}
    #pragma region end
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
    #pragma endregion
}