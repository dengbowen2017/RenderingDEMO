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

    void OpenGLRHI::CreateShaderState()
    {
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

    void OpenGLRHI::SetShaderState(std::shared_ptr<VertexDeclaration> vd)
    {
        std::shared_ptr<OpenGLVertexDeclaration> glvd = std::dynamic_pointer_cast<OpenGLVertexDeclaration>(vd);
        
        unsigned int index = 0;
        for (const auto& e : glvd->m_Elements)
        {
            //switch to new OpenGL api in 4.3
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, e.Count, e.Type, GL_FALSE, glvd->m_Stride, (const void*)e.Offset);
        }
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

    void OpenGLRHI::Draw(unsigned int count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}