#include "graphics.h"
#include "util.h"

struct buffer_element
{
	GLenum type;
	GLboolean normalized;
	size_t size = 0;
	size_t offset = 0;
};

static size_t get_type_size(GLenum type)
{
	switch (type)
	{
		case GL_FLOAT: return 4;
		case GL_FLOAT_VEC2: return 4 * 2;
		case GL_FLOAT_VEC3: return 4 * 3;
		case GL_FLOAT_VEC4: return 4 * 4;
		case GL_FLOAT_MAT2: return 4 * 2 * 2;
		case GL_FLOAT_MAT3: return 4 * 3 * 3;
		case GL_FLOAT_MAT4: return 4 * 4 * 4;
		case GL_INT: return 4;
		case GL_INT_VEC2: return 4 * 2;
		case GL_INT_VEC3: return 4 * 3;
		case GL_INT_VEC4: return 4 * 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_INT_VEC2: return 4 * 2;
		case GL_UNSIGNED_INT_VEC3: return 4 * 3;
		case GL_UNSIGNED_INT_VEC4: return 4 * 4;
	}

	return 0;
}

static GLenum get_type_base(GLenum type)
{
	switch (type)
	{
		case GL_FLOAT: return GL_FLOAT;
		case GL_FLOAT_VEC2: return GL_FLOAT;
		case GL_FLOAT_VEC3: return GL_FLOAT;
		case GL_FLOAT_VEC4: return GL_FLOAT;
		case GL_FLOAT_MAT2: return GL_FLOAT;
		case GL_FLOAT_MAT3: return GL_FLOAT;
		case GL_FLOAT_MAT4: return GL_FLOAT;
		case GL_INT: return GL_INT;
		case GL_INT_VEC2: return GL_INT;
		case GL_INT_VEC3: return GL_INT;
		case GL_INT_VEC4: return GL_INT;
		case GL_UNSIGNED_INT: return GL_UNSIGNED_INT;
		case GL_UNSIGNED_INT_VEC2: return GL_UNSIGNED_INT;
		case GL_UNSIGNED_INT_VEC3: return GL_UNSIGNED_INT;
		case GL_UNSIGNED_INT_VEC4: return GL_UNSIGNED_INT;
	}

	return 0;
}

static GLenum get_type_components(GLenum type)
{
	switch (type)
	{
		case GL_UNSIGNED_INT: 
		case GL_INT: 
		case GL_FLOAT: return 1;
		case GL_INT_VEC2:
		case GL_UNSIGNED_INT_VEC2: 
		case GL_FLOAT_VEC2: return 2;
		case GL_INT_VEC3: 
		case GL_UNSIGNED_INT_VEC3: 
		case GL_FLOAT_VEC3: return 3;
		case GL_INT_VEC4: 
		case GL_UNSIGNED_INT_VEC4: 
		case GL_FLOAT_VEC4: return 4;
		case GL_FLOAT_MAT2: return 2;
		case GL_FLOAT_MAT3: return 3;
		case GL_FLOAT_MAT4: return 4;
	}

	return 0;
}

GLuint create_shader(const shader_source* sources, uint32_t count)
{
	auto program = glCreateProgram();

	GLenum* glShaderIDs = PK_STACK_ALLOC(GLenum, count);

	int glShaderIDIndex = 0;

	for (auto i = 0; i < count; ++i)
	{
		auto type = sources[i].type;
		const auto& source = sources[i].source;

		auto glShader = glCreateShader(type);

		glShaderSource(glShader, 1, &source, 0);
		glCompileShader(glShader);

		GLint isCompiled = 0;
		glGetShaderiv(glShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &maxLength);

			GLchar* infoLog = PK_STACK_ALLOC(GLchar, maxLength);
			glGetShaderInfoLog(glShader, maxLength, &maxLength, infoLog);

			glDeleteShader(glShader);

			PK_LOGW(infoLog);
			PK_LOGI(source);
			glDeleteShader(glShader);
			continue;
		}

		glAttachShader(program, glShader);
		glShaderIDs[glShaderIDIndex++] = glShader;
	}

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* infoLog = PK_STACK_ALLOC(GLchar, maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

		glDeleteProgram(program);

		for (auto i = 0; i < count; ++i)
		{
			glDeleteShader(glShaderIDs[i]);
		}

		PK_LOGW("Shader link failure! \n%s", infoLog);
		glDeleteProgram(program);
		return 0;
	}

	for (auto i = 0; i < count; ++i)
	{
		glDetachShader(program, glShaderIDs[i]);
		glDeleteShader(glShaderIDs[i]);
	}

	return program;
}

GLuint create_shader(const char* sourceVertex, const char* sourceFragment)
{
	shader_source sources[] = { { GL_VERTEX_SHADER, sourceVertex }, { GL_FRAGMENT_SHADER, sourceFragment } };
	return create_shader(sources, 2);
}

GLuint create_shader(AAssetManager* assetManager, const char* pathVertex, const char* pathFragment)
{
	char* source_vert = get_asset_text(assetManager, pathVertex);
	char* source_frag = get_asset_text(assetManager, pathFragment);

	shader shader = create_shader(source_vert, source_frag);

	free(source_vert);
	free(source_frag);

	return shader;
}

mesh create_mesh(const void* vertices, const uint32_t  vc, const GLuint* indices, const uint32_t ic, const vertex_attribute* attributes, uint32_t ac)
{
	buffer_element* layout = PK_STACK_ALLOC(buffer_element, ac);
	size_t stride = 0u;

	for (uint32_t i = 0u; i < ac; ++i)
	{
		buffer_element& element = layout[i];
		element.offset = stride;
		element.size = get_type_size(attributes[i].type);
		element.type = attributes[i].type;
		element.normalized = attributes[i].normalized;
		stride += element.size;
	}

	mesh newmesh = mesh();
	newmesh.indexCount = ic;

	glGenVertexArrays(1, &newmesh.vertexArrayId);
	glBindVertexArray(newmesh.vertexArrayId);

	glGenBuffers(1, &newmesh.indexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, newmesh.indexBufferId);
	glBufferData(GL_ARRAY_BUFFER, ic * sizeof(GLuint), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newmesh.indexBufferId);

	glGenBuffers(1, &newmesh.vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, newmesh.vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, stride * vc, vertices, GL_STATIC_DRAW);

	for (uint32_t i = 0u; i < ac; ++i)
	{
		buffer_element& element = layout[i];

		switch (element.type)
		{
			case GL_FLOAT:
			case GL_FLOAT_VEC2:
			case GL_FLOAT_VEC3:
			case GL_FLOAT_VEC4:
			case GL_INT:
			case GL_INT_VEC2:
			case GL_INT_VEC3:
			case GL_INT_VEC4:
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i,
					get_type_components(element.type),
					get_type_base(element.type),
					element.normalized,
					stride,
					(const void*)element.offset);
				break;
			}
			case GL_FLOAT_MAT3:
			case GL_FLOAT_MAT4:
			{
				auto count = get_type_components(element.type);

				for (uint8_t j = 0; j < count; ++j)
				{
					glEnableVertexAttribArray(i);
					glVertexAttribPointer(i,
						count,
						get_type_base(element.type),
						element.normalized,
						stride,
						(const void*)(element.offset + sizeof(float) * count * j));
					glVertexAttribDivisor(i, 1);
				}
				break;
			}
		}
	}

    return newmesh;
}

void release_shader(shader* shader)
{
	glDeleteProgram(*shader);
	*shader = 0;
}

void release_mesh(mesh* mesh)
{
	glDeleteVertexArrays(1, &mesh->vertexArrayId);
	glDeleteBuffers(1, &mesh->indexBufferId);
	glDeleteBuffers(1, &mesh->vertexBufferId);
}


void set_float(graphics_context* context, const char* name, float value)
{
	if (context->active_shader != nullptr)
	{
		GLint location = glGetUniformLocation(*context->active_shader, name);

		if (location >= 0)
		{
			glUniform1f(location, value);
		}
	}
}

void set_float4(graphics_context* context, const char* name, const float4& value)
{
	if (context->active_shader != nullptr)
	{
		GLint location = glGetUniformLocation(*context->active_shader, name);

		if (location >= 0)
		{
			glUniform4fv(location, 1, &value.x);
		}
	}
}

void set_float4x4(graphics_context* context, const char* name, const float4x4& value)
{
	if (context->active_shader != nullptr)
	{
		GLint location = glGetUniformLocation(*context->active_shader, name);

		if (location >= 0)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, &value.c0.x);
		}
	}
}


void set_pass(graphics_context* context, const shader* shader)
{
	if (context->active_shader == shader)
	{
		return;
	}

	glUseProgram(*shader);
	context->active_shader = shader;

	set_float4x4(context, UNIFORM_NAME_MATRIX_VP, context->matrix_vp);
	set_float(context, UNIFORM_NAME_TIME, context->time);
	set_float(context, UNIFORM_NAME_DISTANCE, context->distance);
}

void draw_mesh(graphics_context* context, const mesh* mesh)
{
	if (context->active_mesh != mesh)
	{
		glBindVertexArray(mesh->vertexArrayId);
		context->active_mesh = mesh;
	}

	glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid*)(size_t)0);

}

void draw_mesh(graphics_context* context, const mesh* mesh, const float4x4& matrix)
{
	set_float4x4(context, UNIFORM_NAME_MATRIX_M, matrix);
	draw_mesh(context, mesh);
}

void draw_mesh(graphics_context* context, const mesh* mesh, const shader* shader)
{
	set_pass(context, shader);
	draw_mesh(context, mesh);
}

void draw_mesh(graphics_context* context, const mesh* mesh, const shader* shader, const float4x4& matrix)
{
	set_pass(context, shader);
	draw_mesh(context, mesh, matrix);
}
