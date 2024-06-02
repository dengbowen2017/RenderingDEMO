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
        this->CreateSwapChain();

        //glGenVertexArrays(1, &m_VAO);
        //glBindVertexArray(m_VAO);
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
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return std::shared_ptr<OpenGLVertexBuffer>(new OpenGLVertexBuffer(size, VBO));
    }

    void OpenGLRHI::CreateIndexBuffer()
    {
    }

    void OpenGLRHI::CreateShader()
    {
    }

    void OpenGLRHI::CreateVertexDeclaration()
    {
    }

    void OpenGLRHI::SetVertexShaderLayout()
    {
    }

    void OpenGLRHI::SetVertexBuffer(std::shared_ptr<VertexBuffer> vb)
    {
    }

    void OpenGLRHI::ClearBackBuffer(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRHI::SwapBuffer()
    {
        glfwSwapBuffers(m_Window);
    }

    void OpenGLRHI::Draw()
    {
    }


}