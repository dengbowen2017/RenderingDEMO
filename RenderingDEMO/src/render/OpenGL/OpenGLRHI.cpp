#include "OpenGLRHI.h"
#include "OpenGLRHIResource.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h>

namespace RenderingDEMO
{
    OpenGLRHI::~OpenGLRHI()
    {
    }

    void OpenGLRHI::Initialize(std::shared_ptr<Window> window)
    {
        m_Window = window->GetWindowPointer();
        m_WindowSize = window->GetWindowSize();

        //create context
        glfwMakeContextCurrent(m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            spdlog::error("Failed to initialize GLAD");
            return;
        }

        //create swapchain
        //TODO: add window resize callback to reset the viewport
        CreateSwapChain();

        glCreateVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
    }

    void OpenGLRHI::CreateSwapChain()
    {
        glViewport(0, 0, m_WindowSize[0], m_WindowSize[1]);
    }

    void OpenGLRHI::RecreateSwapChain()
    {
        //when windowsize is changed, swapchain need to be recreated.
        glViewport(0, 0, m_WindowSize[0], m_WindowSize[1]);
    }


    std::shared_ptr<VertexBuffer> OpenGLRHI::CreateVertexBuffer(void* data, unsigned int size)
    {
        unsigned int VBO;
        glCreateBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return std::shared_ptr<OpenGLVertexBuffer>(new OpenGLVertexBuffer(size, VBO));
    }

    std::shared_ptr<IndexBuffer> OpenGLRHI::CreateIndexBuffer(void* data, unsigned int size)
    {
        unsigned int VEO;
        glCreateBuffers(1, &VEO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return std::shared_ptr<OpenGLIndexBuffer>(new OpenGLIndexBuffer(size / sizeof(unsigned int), VEO));
    }

    std::shared_ptr<VertexDeclaration> OpenGLRHI::CreateVertexDeclaration(const std::vector<VertexElement>& elements)
    {
        return std::shared_ptr<OpenGLVertexDeclaration>(new OpenGLVertexDeclaration(elements));
    }

    std::shared_ptr<VertexShader> OpenGLRHI::CreateVertexShader(const std::string& file_path)
    {
        std::string vertexShaderSource = ReadFromFile(file_path);
        const char* source = vertexShaderSource.c_str();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &source, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            spdlog::error("Shader Vertex Compilation Failed:", infoLog);
        }

        return std::shared_ptr<OpenGLVertexShader>(new OpenGLVertexShader(vertexShader));
    }

    std::shared_ptr<PixelShader> OpenGLRHI::CreatePixelShader(const std::string& file_path)
    {
        std::string pixelShaderSource = ReadFromFile(file_path);
        const char* source = pixelShaderSource.c_str();

        unsigned int pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(pixelShader, 1, &source, nullptr);
        glCompileShader(pixelShader);

        int success;
        char infoLog[512];
        glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(pixelShader, 512, nullptr, infoLog);
            spdlog::error("Shader pixel Compilation Failed:", infoLog);
        }

        return std::shared_ptr<OpenGLPixelShader>(new OpenGLPixelShader(pixelShader));
    }

    std::shared_ptr<BoundShaderState> OpenGLRHI::CreateBoundShaderState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd)
    {
        std::shared_ptr<OpenGLVertexShader> glvs = std::dynamic_pointer_cast<OpenGLVertexShader>(vs);
        std::shared_ptr<OpenGLPixelShader> glps = std::dynamic_pointer_cast<OpenGLPixelShader>(ps);
        std::shared_ptr<OpenGLVertexDeclaration> glvd = std::dynamic_pointer_cast<OpenGLVertexDeclaration>(vd);

        return std::shared_ptr<BoundShaderState>(new OpenGLBoundShaderState(glvs, glps, glvd));
    }

    void OpenGLRHI::SetVertexBuffer(std::shared_ptr<VertexBuffer> vb)
    {
        std::shared_ptr<OpenGLVertexBuffer> glVB = std::dynamic_pointer_cast<OpenGLVertexBuffer>(vb);
        glBindBuffer(GL_ARRAY_BUFFER, glVB->GetID());
    }

    void OpenGLRHI::SetIndexBuffer(std::shared_ptr<IndexBuffer> ib)
    {
        std::shared_ptr<OpenGLIndexBuffer> glIB = std::dynamic_pointer_cast<OpenGLIndexBuffer>(ib);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIB->GetID());
    }

    void OpenGLRHI::SetVertexLayout(std::shared_ptr<VertexDeclaration> vd)
    {
        std::shared_ptr<OpenGLVertexDeclaration> glvd = std::dynamic_pointer_cast<OpenGLVertexDeclaration>(vd);
        
        for (const auto& e : glvd->GetElements())
        {
            //TODO: switch to new OpenGL api in 4.3
            glEnableVertexAttribArray(e.Index);
            glVertexAttribPointer(e.Index, e.Count, e.Type, GL_FALSE, glvd->GetStride(), (const void*)e.Offset);
        }
    }

    void OpenGLRHI::SetBoundShaderState(std::shared_ptr<BoundShaderState> state)
    {
        std::shared_ptr<OpenGLBoundShaderState> glState = std::dynamic_pointer_cast<OpenGLBoundShaderState>(state);

        SetVertexLayout(glState->GetVertexDeclaration());
        glUseProgram(glState->GetID());
    }

    void OpenGLRHI::ClearBackBuffer()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRHI::SwapBuffer()
    {
        glfwSwapBuffers(m_Window);
    }

    void OpenGLRHI::Draw(unsigned int count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    std::string OpenGLRHI::ReadFromFile(const std::string& file_path)
    {
        std::string shaderCode;
        std::ifstream shaderFile;

        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            shaderFile.open(file_path);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderCode = shaderStream.str();
        }
        catch (const std::ifstream::failure& e)
        {
            spdlog::error("Shader File Not Successfully Read:", e.what());
        }

        return shaderCode;
    }
}