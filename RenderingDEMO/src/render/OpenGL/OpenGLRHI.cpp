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

        glfwMakeContextCurrent(m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            spdlog::error("Failed to initialize GLAD");
            return;
        }

        glViewport(0, 0, m_WindowSize[0], m_WindowSize[1]);

        unsigned int vao;
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);
        m_VAO = vao;
    }

    void OpenGLRHI::RecreateSwapChain(int width, int height)
    {
        m_WindowSize = { width, height };
        glViewport(0, 0, m_WindowSize[0], m_WindowSize[1]);
    }

    std::shared_ptr<VertexBuffer> OpenGLRHI::CreateVertexBuffer(const void* data, unsigned int size, unsigned int stride)
    {
        unsigned int VBO;
        glCreateBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return std::shared_ptr<OpenGLVertexBuffer>(new OpenGLVertexBuffer(VBO, size, stride));
    }

    std::shared_ptr<IndexBuffer> OpenGLRHI::CreateIndexBuffer(const void* data, unsigned int size)
    {
        unsigned int VEO;
        glCreateBuffers(1, &VEO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return std::shared_ptr<OpenGLIndexBuffer>(new OpenGLIndexBuffer(VEO, size / sizeof(unsigned int)));
    }

    std::shared_ptr<UniformBuffer> OpenGLRHI::CreateUniformBuffer(unsigned int size)
    {
        unsigned int UBO;
        glCreateBuffers(1, &UBO);
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        return std::shared_ptr<OpenGLUniformBuffer>(new OpenGLUniformBuffer(UBO, size));
    }

    std::shared_ptr<VertexDeclaration> OpenGLRHI::CreateVertexDeclaration(const std::vector<VertexElement>& elements)
    {
        return std::shared_ptr<OpenGLVertexDeclaration>(new OpenGLVertexDeclaration(elements));
    }

    std::shared_ptr<VertexShader> OpenGLRHI::CreateVertexShader(const std::wstring& filePath)
    {
        std::string vertexShaderSource = ReadFromFile(filePath);
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
            spdlog::error("Shader Vertex Compilation Failed: {0}", infoLog);
        }

        return std::shared_ptr<OpenGLVertexShader>(new OpenGLVertexShader(vertexShader));
    }

    std::shared_ptr<PixelShader> OpenGLRHI::CreatePixelShader(const std::wstring& filePath)
    {
        std::string pixelShaderSource = ReadFromFile(filePath);
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
            spdlog::error("Shader Pixel Compilation Failed: {0}", infoLog);
        }

        return std::shared_ptr<OpenGLPixelShader>(new OpenGLPixelShader(pixelShader));
    }

    std::shared_ptr<PipelineState> OpenGLRHI::CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd)
    {
        std::shared_ptr<OpenGLVertexShader> glvs = std::dynamic_pointer_cast<OpenGLVertexShader>(vs);
        std::shared_ptr<OpenGLPixelShader> glps = std::dynamic_pointer_cast<OpenGLPixelShader>(ps);
        std::shared_ptr<OpenGLVertexDeclaration> glvd = std::dynamic_pointer_cast<OpenGLVertexDeclaration>(vd);

        return std::shared_ptr<OpenGLPipelineState>(new OpenGLPipelineState(glvs, glps, glvd));
    }

    void OpenGLRHI::UpdateUniformBuffer(std::shared_ptr<UniformBuffer> ub, const void* data)
    {
        std::shared_ptr<OpenGLUniformBuffer> glub = std::dynamic_pointer_cast<OpenGLUniformBuffer>(ub);

        unsigned int offset = 0;
        glNamedBufferSubData(glub->GetID(), offset, glub->GetSize(), data);
    }

    void OpenGLRHI::SetVertexBuffer(std::shared_ptr<VertexBuffer> vb)
    {
        std::shared_ptr<OpenGLVertexBuffer> glvb = std::dynamic_pointer_cast<OpenGLVertexBuffer>(vb);
        
        // temp
        unsigned int bindindex = 0;
        unsigned int offset = 0;
        glBindVertexBuffer(bindindex, glvb->GetID(), offset, glvb->GetStride());
    }

    void OpenGLRHI::SetUniformBuffer(std::shared_ptr<UniformBuffer> ub, unsigned int index)
    {
        std::shared_ptr<OpenGLUniformBuffer> glub = std::dynamic_pointer_cast<OpenGLUniformBuffer>(ub);

        glBindBufferBase(GL_UNIFORM_BUFFER, index, glub->GetID());
    }

    void OpenGLRHI::SetPipelineState(std::shared_ptr<PipelineState> state)
    {
        std::shared_ptr<OpenGLPipelineState> glState = std::dynamic_pointer_cast<OpenGLPipelineState>(state);
        std::shared_ptr<OpenGLVertexDeclaration> glvd = glState->m_VertexDeclaration;

        // bind vertex layout
        for (const auto& e : glvd->GetElements())
        {     
            // OpenGL 4.3 ++
            unsigned int bindindex = 0;
            glEnableVertexAttribArray(e.Index);
            glVertexAttribFormat(e.Index, e.Count, e.Type, GL_FALSE, e.Offset);
            glVertexAttribBinding(e.Index, bindindex);
        }

        // bind shaders
        glUseProgram(glState->m_ID);

        // set rasterizer state
        glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

        // set depth state
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRHI::ClearBackBuffer()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRHI::SwapBuffer()
    {
        glfwSwapBuffers(m_Window);
    }

    void OpenGLRHI::Draw(unsigned int count)
    {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void OpenGLRHI::DrawIndexed(std::shared_ptr<IndexBuffer> ib)
    {
        std::shared_ptr<OpenGLIndexBuffer> glib = std::dynamic_pointer_cast<OpenGLIndexBuffer>(ib);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glib->GetID());
        glDrawElements(GL_TRIANGLES, glib->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    std::string OpenGLRHI::ReadFromFile(const std::wstring& filePath)
    {
        std::string shaderCode;
        std::ifstream shaderFile;

        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            shaderFile.open(filePath);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderCode = shaderStream.str();
        }
        catch (const std::ifstream::failure& e)
        {
            spdlog::error("Shader File Not Successfully Read: {0}", e.what());
        }

        return shaderCode;
    }
}