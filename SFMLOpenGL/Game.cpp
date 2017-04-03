#include <Game.h>
#include <Cube.h>


template  <typename T>
string  tostring(T number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}
GLuint	vsid,		// Vertex Shader ID
		fsid,		// Fragment Shader ID
		progID,		// Program ID
		vao = 0,	// Vertex Array ID
		vbo,		// Vertex Buffer ID
		vib,		// Vertex Index Buffer
		to,			// Texture ID 1 to 32
		positionID,	// Position ID
		colorID,	// Color ID
		textureID,	// Texture ID
		uvID,		// UV ID
		mvpID;		// Model View Projection ID

//const string filename = "coordinates.tga";
//const string filename = "cube.tga";
const string filename = "grid.tga";
//const string filename = "grid_wip.tga";
//const string filename = "minecraft.tga";
//const string filename = "texture.tga";
//const string filename = "texture_2.tga";
//const string filename = "uvtemplate.tga";
Vector2f velocity(0.0f, 1.0f);
Vector2f position(400, 399);
Vector2f impulse(20.7f, 20.7f);
Vector2f gravity(0.0f, 9.8f);
const float acceleration = 0.25;
float const pixelsTometres = 20;



const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
sf::Time timeSinceLastUpdate = sf::Time::Zero;

int width;			// Width of texture
int height;			// Height of texture
int comp_count;		// Component of texture

unsigned char* img_data;		// image data

mat4 mvp, projection, view, modelWall1, modelWall2; //model, model[1], model[2], model[3], model[4];			// Model View Projection
mat4 model[5];

Font font;

Game::Game() : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing"),
	m_player(glm::vec3(0, 0, 0))
	
{
}

Game::Game(sf::ContextSettings settings) : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing", 
	sf::Style::Default, 
	settings),
	m_player(glm::vec3(0, 0, 0))

{
}

Game::~Game(){}


void Game::run()
{

	initialize();
	font.loadFromFile("./Assets/Fonts/BAUHS93.TTF");

	Event event;

	while (window.isOpen()){

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif
	//	bool move = false;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Set Model Rotation
				float rotation(.05);
				m_player.updateRot(rotation);
				model[0] = rotate(model[0], rotation, glm::vec3(0, 1, 0)); // Rotate
			//	model[0] = rotate(model[0], 0.20f, glm::vec3(0, 1, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// Set Model Rotation
				float rotation(-.05);
				m_player.updateRot(rotation);
				model[0] = rotate(model[0], rotation, glm::vec3(0,1 , 0)); // Rotate
			//	model[0] = rotate(model[0], -0.20f, glm::vec3(0, 1, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				// Set Model Rotation
				float rotation(-.05);
				m_player.updateRot(rotation);
				model[0] = rotate(model[0], rotation, glm::vec3(1, 0, 0)); // Rotate
				//model[0] = rotate(model[0], -0.20f, glm::vec3(1, 0, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				// Set Model Rotation
				float rotation(.05);
				m_player.updateRot(rotation);
				model[0] = rotate(model[0], rotation, glm::vec3(1, 0, 0)); // Rotate
			//	model[0] = translate(model[0],  glm::vec3(1, 0, 0)); // Rotate
			}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			//{
			//	glm::vec3 vec(0, -0.05, 0);
			//	m_player.updatePos(vec);
			//	model[0] = translate(model[0], vec); // move

			//	//model = 
			//}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			//{
			//	glm::vec3 vec(0, 0.05, 0);
			//	m_player.updatePos(vec);
			//	model[0] = translate(model[0], vec);   // move

			//												   
			//}
		

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			{

				model[0] = translate(model[0], glm::vec3(0, 0, 1)); // move


			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			{
				model[0] = translate(model[0], glm::vec3(0, 0, -1)); // move


			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				
				model[0][3].y += 0.200;

				if (model[0][3].y >= 1)
				{
					model[0][3].y -= 0.700;

					if (model[0][3].y == 1)
					{
						break;

					}
				}
				/*velocity.y = impulse.y*pixelsTometres;
			
				model[0] = translate(model[0], glm::vec3(0, 0.05, 0));
			
				model[0] = translate(model[0], glm::vec3(0, -0.04, 0));*/
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}


			if (move == false)
			{

				velocity.y = 0;
				position.y = 400;
			//	model[0].setPosition(position);
			}
			else
			{
				position.y = 400;
				//model[0].setPosition(position);
				float temp = (velocity.y / 2.0f);
				velocity.y = -(velocity.y);
				velocity.y += temp;

			}
		}


		for (int i = 1; i < 5; i++)
		{
			distance = std::sqrt((model[0][3].x- model[i][3].x) * (model[0][3].x - model[i][3].x)) + ((model[0][3].z - model[i][3].z) * (model[0][3].z - model[i][3].z));
			//	std::cout << "Distance " << distance << std::endl;
			//model[0][3].z <= model[i][3].z
			if (distance <= 2 )
			{
				//model[0][3].z = 10;
				//lives -= 1;
				std::cout << "Hit!!!!!" << std::endl;
				//window.close();
				m_gameState = gameState::GameOver;
			}
		}

		//std::cout << "Lives: " << lives << std::endl;
		update();
		render();
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Calling Cleanup...");
#endif
	unload();

}

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	//Copy UV's to all faces
	for (int i = 1; i < 6; i++)
		memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	glGenVertexArrays(1, &vao); //Gen Vertex Array
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo); //Gen Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Vertices 3 x,y,z , Colors 4 RGBA, UV/ST 2
	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); //Gen Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	//Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);
	string shader = readMethod();
	const char* vs_src = shader.c_str();
		//"#version 400\n\r"
		//""
		/*"layout(location = 0) in vec3 sv_position; //Use for individual Buffers"
		"layout(location = 1) in vec4 sv_color; //Use for individual Buffers"
		"layout(location = 2) in vec2 sv_texel; //Use for individual Buffers"*/
		//""
		//"in vec3 sv_position;"
		//"in vec4 sv_color;"
		//"in vec2 sv_uv;"
		//""
		//"out vec4 color;"
		//"out vec2 uv;"
		//""
		//"uniform mat4 sv_mvp;"
		//""
		//"void main() {"
		//"	color = sv_color;"
		//"	uv = sv_uv;"
		////"	gl_Position = vec4(sv_position, 1);"
		//"	gl_Position = sv_mvp * vec4(sv_position, 1);"
		//"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
	glCompileShader(vsid);

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}
	string frag = fragmentRead();
	const char* fs_src = frag.c_str();
		//"#version 400\n\r"
		//""
		//"uniform sampler2D f_texture;"
		//""
		//"in vec4 color;"
		//"in vec2 uv;"
		//""
		//"out vec4 fColor;"
		//""
		//"void main() {"
		////"	vec4 lightColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); "
		////"	fColor = vec4(0.50f, 0.50f, 0.50f, 1.0f);"
		////"	fColor = texture2D(f_texture, uv);"
		////"	fColor = color * texture2D(f_texture, uv);"
		////"	fColor = lightColor * texture2D(f_texture, uv);"
		////"	fColor = color + texture2D(f_texture, uv);"
		////"	fColor = color - texture2D(f_texture, uv);"
		//"	fColor = color;"
		//"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);

	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();
	glAttachShader(progID, vsid);
	glAttachShader(progID, fsid);
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	//Use Progam on GPU
	//glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,		//2D Texture Image
		0,					//Mipmapping Level 
		GL_RGBA,			//GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,				//Width
		height,				//Height
		0,					//Border
		GL_RGBA,			//Bitmap
		GL_UNSIGNED_BYTE,	//Specifies Data type of image data
		img_data				//Image Dataa
		);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	uvID = glGetAttribLocation(progID, "sv_uv");
	textureID = glGetUniformLocation(progID, "f_texture");
	mvpID = glGetUniformLocation(progID, "sv_mvp");

	// Projection Matrix 
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		1.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
		);

	// Camera Matrix
	view = lookAt(
		vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		vec3(0.0f, 0.0f, 0.0f),	// Camera looking at origin
		vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
		);

	for (size_t i = 0; i < 5; i++)
	{
		model[i] = mat4(
			1.0f
		);
	}
	
	model[1] = translate(model[1], vec3(5, 0, 0));
	model[2] = translate(model[2], vec3(-5, 0, 0));
	model[3] = translate(model[2], vec3(-10, 0, -5));
	model[4] = translate(model[2], vec3(10, 0, -5));
	
	modelWall1 = mat4(
		1.0f
	);

	modelWall2 = mat4(
		1.0f
	);

	modelWall1 = translate(modelWall1, vec3(12, 0, 0));
	modelWall1 = scale(modelWall1, vec3(1, 2, 200));
	modelWall2 = translate(modelWall2, vec3(-12, 0, 0));
	modelWall2 = scale(modelWall2, vec3(1, 2, 200));

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

void Game::update()
{
	
#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
#endif
	switch (m_gameState)
	{
		//	if(model == 200)
	case gameState::Playing:
		for (size_t i = 1; i < 5; i++)
		{
			model[i] = translate(model[i], vec3(0, 0, 0.010 + (i / 40.0)));
		}
		for (size_t i = 1; i < 5; i++)
		{
			if (model[i][3].z > 10)
			{
				model[i] = translate(model[i], vec3(0, 0, -100));
				model[i] = translate(model[i], vec3(2, 0, 0));

				switch (i)
				{
				case 1:
					if (model[i][3].x > 8)
					{
						model[i] = translate(model[i], vec3(-16, 0, 0));
					}
					break;
				case 2:
					if (model[i][3].x > 8)
					{
						model[i] = translate(model[i], vec3(-14, 0, 0));
					}
					break;
				case 3:
					if (model[i][3].x > 8)
					{
						model[i] = translate(model[i], vec3(-10, 0, 0));
					}
					break;
				case 4:
					if (model[i][3].x > 8)
					{
						model[i] = translate(model[i], vec3(-4, 0, 0));
					}
				}
			}
		}
		//model[2] = translate(model[2], vec3(0.01f, 0, 0));
		//model[2] = rotate(model[2], 0.001f, vec3(1, 0, 0));
		//model[3] = rotate(model[3], 0.001f, vec3(5, 0, 0));
		//model[4] = rotate(model[4], 0.001f, vec3(10, 0, 0));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (model[0][3].x < 10)
			{
				glm::vec3 vec(0.010, 0, 0);
				m_player.updatePos(vec);
				model[0] = translate(model[0], vec);  // move
				view = translate(view, glm::vec3(-0.010, 0, 0));
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (model[0][3].x > -10)
			{

				glm::vec3 vec(-0.010, 0, 0);
				m_player.updatePos(vec);
				model[0] = translate(model[0], vec); // move
				view = translate(view, glm::vec3(0.010, 0, 0));
			}
		}

		
		break;

	case gameState::GameOver:
		break;
	}
	//distance += 0.1 / 0.60;
}

void Game::render()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	string hud = "" + string("Distance: ") + tostring((int)timer.getElapsedTime().asSeconds());
	Text text(hud, font);


	
	
	switch (m_gameState)
	{

	

	case gameState::Playing:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.pushGLStates();
	

		text.setColor(sf::Color(255, 255, 255, 170));
		text.setPosition(50.f, 50.f);
		window.draw(text);

		//SFML HERE
		window.popGLStates();
		//Use Progam on GPU
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);
		glUseProgram(progID);
		cubeRender(modelWall1);
		cubeRender(modelWall2);

		for (size_t i = 0; i < 5; i++)
		{
			cubeRender(model[i]);
		}

		// right bottom
		glViewport(window.getSize().x / 2, window.getSize().y / 4, window.getSize().x/2, window.getSize().y/2);
		glLoadIdentity();
		gluLookAt(5.0f, 5.0f, 5.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);
		for (size_t i = 0; i < 5; i++)
		{
			cubeRender(model[i]);
		}
		cubeRender(modelWall1);
		cubeRender(modelWall2);
		// left bottom
		glViewport(0, window.getSize().y / 4, window.getSize().x / 2, window.getSize().y/2);
		glLoadIdentity();
		gluLookAt(5.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);
		for (size_t i = 0; i < 5; i++)
		{
			cubeRender(model[i]);
		}
		cubeRender(modelWall1);
		cubeRender(modelWall2);

	
		window.display();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (window.getSize().x <= window.getSize().y)
			glOrtho(-2.0, 2.0,
				-2.0 * (GLfloat)window.getSize().y / (GLfloat)window.getSize().x, 2.0 * (GLfloat)window.getSize().y / (GLfloat)window.getSize().x,
				-10.0, 100.0);
		else
			glOrtho(-2.0 * (GLfloat)window.getSize().x / (GLfloat)window.getSize().y, 2.0 * (GLfloat)window.getSize().x / (GLfloat)window.getSize().y,
				-2.0, 2.0,
				-10.0, 100.0);

		glMatrixMode(GL_MODELVIEW);

		//mvp = projection * view * model[0];
		////VBO Data....vertices, colors and UV's appended
		//glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
		//glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
		//glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

		//// Send transformation to shader mvp uniform
		//glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

		////Set Active Texture .... 32
		//glActiveTexture(GL_TEXTURE0);
		//glUniform1i(textureID, 0);

		////Set pointers for each parameter (with appropriate starting positions)
		////https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
		//glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
		//glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));
		//
		////Enable Arrays
		//glEnableVertexAttribArray(positionID);
		//glEnableVertexAttribArray(colorID);
		//glEnableVertexAttribArray(uvID);

		////Draw Element Arrays
		//glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

		/*-------------------------------------------------------------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------------------------------------*/
		window.display();

		//Disable Arrays
		glDisableVertexAttribArray(positionID);
		glDisableVertexAttribArray(colorID);
		glDisableVertexAttribArray(uvID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		//glUseProgram(0);
	//	glTexEnvfv(0, 0, 0);
		break;

	case gameState::GameOver:


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.pushGLStates();
		string hud = "Game Over";
		Text text2(hud, font);
		text2.setColor(sf::Color(255, 0, 0, 250));
		text2.setPosition(250.f, 250.f);
		window.draw(text2);

		//SFML HERE
		window.popGLStates();
		window.display();
		break;

	}

}

void Game::cubeRender(mat4 &modelRef)
{
	mvp = projection * view * modelRef;
	
	//VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	// Send transformation to shader mvp uniform
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	//Set pointers for each parameter (with appropriate starting positions)
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(uvID);

	//Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);




}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);	//Delete Shader
	glDeleteBuffers(1, &vbo);	//Delete Vertex Buffer
	glDeleteBuffers(1, &vib);	//Delete Vertex Index Buffer
	stbi_image_free(img_data);		//Free image
}

String	Game::readMethod()
{
	string line;
	string shader;
	ifstream myfile;
	myfile.open("../Shades.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			shader += line + "\n";
		}
		myfile.close();
	}
	else cout << "Unable to open file" <<std::endl;

	return shader;

}


String Game::fragmentRead()
{
	string line;
	string frag;
	ifstream myfile;
	myfile.open("../Fragments.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			frag += line + "\n";
		}
		myfile.close();
	}
	else cout << "Unable to open file" << std::endl;

	return frag;



}