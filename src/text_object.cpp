#include "polyscope/text_object.h"

namespace polyscope {

const std::string TextObject::structureTypeName = "Text Object";

TextObject::TextObject(std::string name, std::string textContent,
                       glm::vec3 pos, float scale)
  : QuantityStructure<TextObject>(name, typeName()), 
    textContent(textContent), position(pos), scale(scale) {
  
  buildMesh();
  updateObjectSpaceBounds();
}

void TextObject::buildMesh() {
  float x = position.x, y = position.y, z = position.z;

  std::vector<glm::vec3> vertexPositions;
  std::vector<std::vector<size_t>> faceIndices;

  vertexPositions.push_back(glm::vec3(x, y, z));
  vertexPositions.push_back(glm::vec3(x, y + scale, z));

  for (size_t i = 0; i < textContent.size(); i++) {
    float x_coord = x + scale * (i + 1);
    vertexPositions.push_back(glm::vec3(x_coord, y, z));
    vertexPositions.push_back(glm::vec3(x_coord, y + scale, z));

    size_t j = 2 * i;
    std::vector<size_t> f1 {j, j+3, j+1};
    std::vector<size_t> f2 {j, j+2, j+3};
    faceIndices.push_back(f1);
    faceIndices.push_back(f2);
  }

  SurfaceMesh* s = new SurfaceMesh(name, vertexPositions, faceIndices);
  textMesh = std::unique_ptr<SurfaceMesh>(s);
}

void TextObject::draw() {
  if (!isEnabled()) return;
  textMesh->draw();
}

std::string TextObject::typeName() { return structureTypeName; }

void TextObject::updateObjectSpaceBounds() {
  objectSpaceBoundingBox = textMesh->boundingBox();
  objectSpaceLengthScale = textMesh->lengthScale();
};

void TextObject::drawDelayed() {};
void TextObject::drawPick() {};
void TextObject::buildCustomUI() {};
void TextObject::buildPickUI(size_t localPickID) {};

TextObject* registerTextObject(std::string name, std::string textContent,
                               glm::vec3 pos, float scale) {
  checkInitialized();
  TextObject* t = new TextObject(name, textContent, pos, scale);

  bool success = registerStructure(t);
  if (!success) {
    safeDelete(t);
  }
  return t;
}


} // namespace polyscope
