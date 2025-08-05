
#include "mdcpp/texture.hpp"
#include <mdcpp/drawables/drawables.hpp>
#include <mdcpp/utils/definitions.h>



namespace mdcpp {


enum class RenderType {
	TEXTURE,
	NO_FILL, // Wireframe
};

class Vertices: public Drawable {
public:
	Vertices(std::vector<Vertex> vertices, RenderType renderType = RenderType::NO_FILL);
	Vertices(std::vector<glm::vec3> vertices, RenderType renderType = RenderType::NO_FILL);
	Vertices(std::vector<Triangle> triangles, RenderType renderType = RenderType::NO_FILL);


	void draw() override;
	void setTexture(Texture* texture) { m_texture = texture; }
private:
	std::vector<Vertex> m_vertices;
	std::vector<glm::vec3> m_points;
	void setup() override;
	void updateBuffer();
	RenderType m_renderType;

	
	Texture* m_texture;

	size_t m_indexCount;
};



};
