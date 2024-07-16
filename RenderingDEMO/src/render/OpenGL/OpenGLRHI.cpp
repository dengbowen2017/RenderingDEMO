#include "OpenGLRHI.h"
#include "OpenGLRHIResource.h"
#include "OpenGLRHIState.h"

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

    std::shared_ptr<RasterizerState> OpenGLRHI::CreateRasterizerState(const RasterizerStateInitializer& initializer)
    {
        OpenGLRasterizerState* state = new OpenGLRasterizerState;
        state->m_FillMode = TranslateFillMode(initializer.FillMode);
        state->m_CullMode = TranslateCullMode(initializer.CullMode);

        return std::shared_ptr<OpenGLRasterizerState>(state);
    }

    std::shared_ptr<DepthStencilState> OpenGLRHI::CreateDepthStencilState(const DepthStencilStateInitializer& initializer)
    {
        OpenGLDepthStencilState* state = new OpenGLDepthStencilState;
        state->m_DepthFunc = TranslateCompareFunction(initializer.DepthTest);
        state->m_DepthMask = initializer.EnableDepthWrite ? GL_TRUE : GL_FALSE;

        return std::shared_ptr<OpenGLDepthStencilState>(state);
    }

    std::shared_ptr<SamplerState> OpenGLRHI::CreateSamplerState(const SamplerStateInitializer& initializer)
    {
        unsigned int samplerID;
        glCreateSamplers(1, &samplerID);
        
        switch (initializer.Filter)
        {
        case SamplerFilter::Nearest:
            if (initializer.MinMipLevel == 0 && initializer.MaxMipLevel == 0)
            {
                glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }
            else
            {
                glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            }
            break;
        case SamplerFilter::Bilinear:
            if (initializer.MinMipLevel == 0 && initializer.MaxMipLevel == 0)
            {
                glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }
            else
            {
                glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            }
            break;
        case SamplerFilter::Trilinear:
            if (initializer.MinMipLevel == 0 && initializer.MaxMipLevel == 0)
            {
                glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }
            else
            {
                glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
            break;
        }

        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, TranslateAddressMode(initializer.AddressU));
        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, TranslateAddressMode(initializer.AddressV));
        glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, TranslateAddressMode(initializer.AddressW));
        glSamplerParameterfv(samplerID, GL_TEXTURE_BORDER_COLOR, initializer.BorderColor);

        OpenGLSamplerState* state = new OpenGLSamplerState;
        state->m_ID = samplerID;

        return std::shared_ptr<SamplerState>(state);
    }

    std::shared_ptr<Texture2D> OpenGLRHI::CreateTexture2D(unsigned int width, unsigned int height, unsigned int numMips, unsigned int numSamples, unsigned int flags, TextureFormat format, const void* data)
    {
        unsigned int texID;
        glCreateTextures(GL_TEXTURE_2D, 1, &texID);

        GLint texFormat = FindTextureInternalFormat(format);
        GLenum texResFormat = FindTextureResourceFormat(texFormat);
        GLenum texResType = FindTextureResourceType(texFormat);

        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, texFormat, width, height, 0, texResFormat, texResType, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        return std::shared_ptr<OpenGLTexture2D>(new OpenGLTexture2D(width, height, numMips, numSamples, flags, format, texID));
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

    std::shared_ptr<VertexShader> OpenGLRHI::CreateVertexShader(const std::wstring& fileName)
    {
        std::wstring filePath = L"../shader/OpenGL/" + fileName + L".glsl";

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

    std::shared_ptr<PixelShader> OpenGLRHI::CreatePixelShader(const std::wstring& fileName)
    {
        std::wstring filePath = L"../shader/OpenGL/" + fileName + L".glsl";

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

    std::shared_ptr<RenderTarget> OpenGLRHI::CreateRenderTarget(std::shared_ptr<Texture2D> colorTex, std::shared_ptr<Texture2D> depthTex)
    {
        return std::shared_ptr<OpenGLRenderTarget>(new OpenGLRenderTarget(colorTex, depthTex));
    }

    std::shared_ptr<PipelineState> OpenGLRHI::CreatePipelineState(std::shared_ptr<VertexShader> vs, std::shared_ptr<PixelShader> ps, std::shared_ptr<VertexDeclaration> vd, std::shared_ptr<RasterizerState> rasterState, std::shared_ptr<DepthStencilState> depthState)
    {
        std::shared_ptr<OpenGLVertexShader> glvs = std::dynamic_pointer_cast<OpenGLVertexShader>(vs);
        std::shared_ptr<OpenGLPixelShader> glps = std::dynamic_pointer_cast<OpenGLPixelShader>(ps);
        std::shared_ptr<OpenGLVertexDeclaration> glvd = std::dynamic_pointer_cast<OpenGLVertexDeclaration>(vd);
        std::shared_ptr<OpenGLRasterizerState> glrasterState = std::dynamic_pointer_cast<OpenGLRasterizerState>(rasterState);
        std::shared_ptr<OpenGLDepthStencilState> gldepthState = std::dynamic_pointer_cast<OpenGLDepthStencilState>(depthState);

        return std::shared_ptr<OpenGLPipelineState>(new OpenGLPipelineState(glvs, glps, glvd, glrasterState, gldepthState));
    }

    void OpenGLRHI::UpdateUniformBuffer(std::shared_ptr<UniformBuffer> ub, const void* data)
    {
        std::shared_ptr<OpenGLUniformBuffer> glub = std::dynamic_pointer_cast<OpenGLUniformBuffer>(ub);

        unsigned int offset = 0;
        glNamedBufferSubData(glub->GetID(), offset, glub->GetSize(), data);
    }

    void OpenGLRHI::SetTexture(std::shared_ptr<Texture> texture, unsigned int index)
    {
        std::shared_ptr<OpenGLTexture2D> gltex = std::dynamic_pointer_cast<OpenGLTexture2D>(texture);
        glBindTextureUnit(index, gltex->GetID());
    }

    void OpenGLRHI::SetSamplerState(std::shared_ptr<SamplerState> sampler, unsigned int index)
    {
        std::shared_ptr<OpenGLSamplerState> glsampler = std::dynamic_pointer_cast<OpenGLSamplerState>(sampler);
        glBindSampler(index, glsampler->m_ID);
    }

    void OpenGLRHI::SetVertexBuffer(std::shared_ptr<VertexBuffer> vb)
    {
        std::shared_ptr<OpenGLVertexBuffer> glvb = std::dynamic_pointer_cast<OpenGLVertexBuffer>(vb);
        
        // temp
        unsigned int bindindex = 0;
        unsigned int offset = 0;
        glBindVertexBuffer(bindindex, glvb->GetID(), offset, glvb->GetStride());
    }

    void OpenGLRHI::SetUniformBuffer( std::shared_ptr<UniformBuffer> ub, unsigned int index)
    {
        std::shared_ptr<OpenGLUniformBuffer> glub = std::dynamic_pointer_cast<OpenGLUniformBuffer>(ub);
        glBindBufferBase(GL_UNIFORM_BUFFER, index, glub->GetID());
    }

    void OpenGLRHI::SetRenderTarget(std::shared_ptr<RenderTarget> rt)
    {
        if (rt == nullptr)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        else
        {
            std::shared_ptr<OpenGLRenderTarget> glTarget = std::dynamic_pointer_cast<OpenGLRenderTarget>(rt);
            glBindFramebuffer(GL_FRAMEBUFFER, glTarget->GetID());
        }
    }

    void OpenGLRHI::SetViewPort(float width, float height)
    {
        if (width == 0 && height == 0)
        {
            glViewport(0, 0, m_WindowSize[0], m_WindowSize[1]);
        }
        else
        {
            glViewport(0, 0, static_cast<GLuint>(width), static_cast<GLuint>(height));
        }
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
        glPolygonMode(GL_FRONT, glState->m_RasterizerState->m_FillMode);
        glEnable(GL_CULL_FACE);
        glCullFace(glState->m_RasterizerState->m_CullMode);

        // set depth state
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(glState->m_DepthStencilState->m_DepthFunc);
        glDepthMask(glState->m_DepthStencilState->m_DepthMask);
    }

    void OpenGLRHI::ClearBackBuffer()
    {
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRHI::ClearRenderTarget(std::shared_ptr<RenderTarget> target)
    {
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
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

    GLint OpenGLRHI::FindTextureInternalFormat(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::R8_UNorm:
            return GL_R8;
        case TextureFormat::R8G8_UNorm:
            return GL_RG8;
        case TextureFormat::R8G8B8A8_UNorm:
            return GL_RGBA;
        case TextureFormat::R32_Typeless:
            return GL_DEPTH_COMPONENT;
        case TextureFormat::R24G8_Typeless:
            return GL_DEPTH24_STENCIL8;
        case TextureFormat::R16G16B16A16_Float:
            return GL_RGBA16F;
        default:
            return GL_NONE;
        }
    }

    GLenum OpenGLRHI::FindTextureResourceFormat(GLint format)
    {
        switch (format)
        {
        case GL_R8:
            return GL_RED;
        case GL_RG8:
            return GL_RG;
        case GL_RGBA:
            return GL_RGBA;
        case GL_DEPTH_COMPONENT:
            return GL_DEPTH_COMPONENT;
        case GL_DEPTH24_STENCIL8:
            return GL_DEPTH_STENCIL;
        case GL_RGBA16F:
            return GL_RGBA;
        default:
            return GL_NONE;
        }
    }

    GLenum OpenGLRHI::FindTextureResourceType(GLint format)
    {
        switch (format)
        {
        case GL_R8:
            return GL_UNSIGNED_BYTE;
        case GL_RG8:
            return GL_UNSIGNED_BYTE;
        case GL_RGBA:
            return GL_UNSIGNED_BYTE;
        case GL_DEPTH_COMPONENT:
            return GL_FLOAT;
        case GL_DEPTH24_STENCIL8:
            return GL_UNSIGNED_INT_24_8;
        case GL_RGBA16F:
            return GL_FLOAT;
        default:
            return GL_NONE;
        }
    }

    GLint OpenGLRHI::TranslateAddressMode(SamplerAddressMode addressMode)
    {
        switch (addressMode)
        {
        case SamplerAddressMode::Mirror:
            return GL_MIRRORED_REPEAT;
        case SamplerAddressMode::Clamp:
            return GL_CLAMP_TO_EDGE;
        case SamplerAddressMode::Border:
            return GL_CLAMP_TO_BORDER;
        default:
            return GL_REPEAT;
        }
    }

    GLenum OpenGLRHI::TranslateCullMode(RasterizerCullMode cullMode)
    {
        switch (cullMode)
        {
        case RasterizerCullMode::Front:
            return GL_FRONT;
        case RasterizerCullMode::Back:
            return GL_BACK;
        default:
            return GL_NONE;
        };
    }

    GLenum OpenGLRHI::TranslateFillMode(RasterizerFillMode fillMode)
    {
        switch (fillMode)
        {
        case RenderingDEMO::RasterizerFillMode::Wireframe:
            return GL_LINE;
        default:
            return GL_FILL;
        }
    }

    GLenum OpenGLRHI::TranslateCompareFunction(DepthCompareFunc compareFunc)
    {
        switch (compareFunc)
        {
        case RenderingDEMO::DepthCompareFunc::Less:
            return GL_LESS;
        case RenderingDEMO::DepthCompareFunc::LessEqual:
            return GL_LEQUAL;
        case RenderingDEMO::DepthCompareFunc::Greater:
            return GL_GREATER;
        case RenderingDEMO::DepthCompareFunc::GreaterEqual:
            return GL_GEQUAL;
        default:
            return GL_ALWAYS;
        }
    }
}