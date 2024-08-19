
#include "polyscope/render/opengl/shaders/text_object_shaders.h"

namespace polyscope {
namespace render {
namespace backend_openGL3 {

// clang-format off

const ShaderStageSpecification TEXT_OBJECT_VERT_SHADER = {
  
  ShaderStageType::Vertex,

  // uniforms
  {
      {"u_modelView", RenderDataType::Matrix44Float},
      {"u_projMatrix", RenderDataType::Matrix44Float},
  },

  // attributes
  {
      {"a_vertexPositions", RenderDataType::Vector3Float},
      {"a_textureCoords", RenderDataType::Vector2Float},
  },

  {}, // textures

  // source
R"(
      uniform mat4 u_modelView;
      uniform mat4 u_projMatrix;

      in vec3 a_vertexPositions;
      in vec2 a_textureCoords;
      out vec2 a_textureCoordsToFrag;

      void main()
      {
          gl_Position = u_projMatrix * u_modelView * vec4(a_vertexPositions, 1.0);
          a_textureCoordsToFrag = a_textureCoords;
      }
)"
};

const ShaderStageSpecification TEXT_OBJECT_FRAG_SHADER = {
 
  ShaderStageType::Fragment,

  {}, // uniforms

  {}, // attributes

  {}, // textures

  // source
R"(
      in vec2 a_textureCoordsToFrag;
      uniform sampler2D t_image;
      layout(location = 0) out vec4 outputF;

      void main()
      {
        float t_val = texture(t_image, a_textureCoordsToFrag).r;
        vec4 sampled = vec4(1.0, 1.0, 1.0, t_val);
        outputF = vec4(0.5, 0.5, 1.0, 1.0) * sampled;
        // vec4 debug = vec4(a_textureCoordsToFrag, 1.0);
        // outputF = vec4(1.0, 0.0, 1.0, 1.0);
        // outputF = vec4(a_textureCoordsToFrag, 0.5, 1.0);
      }

)"
};

// clang-format on

} // namespace backend_openGL3
} // namespace render
} // namespace polyscope
