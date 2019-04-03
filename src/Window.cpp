#include "Window.hpp"

Window::Window()
{

}

Window::~Window()
{
	glfwTerminate();
}

void	Window::handleTime()
{
	float			current_frame;
	static float	last_frame = 0.0f;
	static int		fps = 0;
	static float	fpstime = 0.0f;

	current_frame = glfwGetTime();
	if (last_frame == 0.0f)
		last_frame = current_frame;
	g_deltaTime = current_frame - last_frame;
	last_frame = current_frame;
	fps++;
	fpstime += g_deltaTime;
	if (fpstime >= 1.0f)
	{
		std::cout << "FPS: " << fps << std::endl;
		fpstime -= 1.0f;
		fps = 0;
	}
}

void	Window::init()
{
	if (!glfwInit())
		throw VoxException("ERROR: could not start GLFW3\n");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(Wscreen, Hscreen, "ft_vox", NULL, NULL);
	if (!window)
		throw VoxException("ERROR: could not open window with GLFW3\n");
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	
	programID = s.create_program(s.create_shader((char*)"shaders/vertex.glsl",
			GL_VERTEX_SHADER), s.create_shader((char*)"shaders/fragment.glsl",
			GL_FRAGMENT_SHADER));
	MatrixID = glGetUniformLocation(programID, "MVP");
	grassID = glGetUniformLocation(programID, "grass");
	stoneID = glGetUniformLocation(programID, "stone");
	sandID = glGetUniformLocation(programID, "sand");
	waterID = glGetUniformLocation(programID, "water");
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	std::cout << vendor << " ||| " << renderer << std::endl;
}

void	Window::create_skybox()
{
	float skyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &skyboxVaoID);
	glBindVertexArray(skyboxVaoID);
	
	skybox_programID = s.create_program(s.create_shader((char*)"shaders/v_skybox.glsl",
			GL_VERTEX_SHADER), s.create_shader((char*)"shaders/f_skybox.glsl",
			GL_FRAGMENT_SHADER));
	
	glGenBuffers(1, &skyboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(float), skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	SkyboxProjectionID = glGetUniformLocation(skybox_programID, "projection");
	SkyboxViewID = glGetUniformLocation(skybox_programID, "view");
	skyboxID = glGetUniformLocation(skybox_programID, "skybox");
}

void	Window::loadSkybox()
{
		glDepthMask(GL_FALSE);
		glUseProgram(skybox_programID);
		glBindVertexArray(skyboxVaoID);
		glUniformMatrix4fv(SkyboxProjectionID, 1, GL_FALSE, &g_player.Projection[0][0]);
		glUniformMatrix4fv(SkyboxViewID, 1, GL_FALSE, &glm::mat4(glm::mat3(g_player.View))[0][0]);

		glUniform1i(skyboxID, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);
		glDisableVertexAttribArray(0);
}

void	Window::loop(bool is_seed, unsigned int seed)
{
	ChunkHandler		chunkHandler(is_seed, seed);

	grass = texture.load_cubemap((char*)"texture/grass_top.bmp", (char*)"texture/grass_side.bmp", (char*)"texture/dirt.bmp");
	stone = texture.load_cubemap((char*)"texture/stone.bmp", (char*)"texture/stone.bmp", (char*)"texture/stone.bmp");
	skybox = texture.load_skybox((char*)"texture/top.jpg", (char*)"texture/left.jpg", (char*)"texture/right.jpg", (char*)"texture/back.jpg", (char*)"texture/front.jpg", (char*)"texture/bottom.jpg");
	sand = texture.load_skybox((char*)"texture/sand.jpg", (char*)"texture/sand.jpg", (char*)"texture/sand.jpg", (char*)"texture/sand.jpg", (char*)"texture/sand.jpg", (char*)"texture/sand.jpg");
	water = texture.load_skybox((char*)"texture/water.jpg", (char*)"texture/water.jpg", (char*)"texture/water.jpg", (char*)"texture/water.jpg", (char*)"texture/water.jpg", (char*)"texture/water.jpg");

	glEnable(GL_CULL_FACE); 

	create_skybox();

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		handleTime();
		chunkHandler.MapHandler();
		g_player.mouseControl(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		loadSkybox();
		
		glUseProgram(programID);
		glBindVertexArray(vaoID);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &g_player.mvp[0][0]);

		glUniform1i(grassID, 0);
		glUniform1i(stoneID, 1);
		glUniform1i(sandID, 2);
		glUniform1i(waterID, 3);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, grass);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, stone);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, sand);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, water);

		chunkHandler.LoadChunks();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	exit(0);
}
