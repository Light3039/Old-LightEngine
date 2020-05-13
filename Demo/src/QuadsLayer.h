#pragma once

#include <LightEngine.h>

struct Sprite
{
	glm::vec2 position;
	glm::vec2 size;
	glm::vec4 tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Light::TextureCoordinates* coordinates;	
};

class QuadsLayer : public Light::Layer
{
private:
	std::shared_ptr<Light::Camera> m_Camera;

	std::shared_ptr<Light::TextureArray> m_TextureArray;

	std::vector<Sprite> m_Sprites;
	Sprite* m_SelectedSprite;

	float m_Angle;
	bool b_BoundToTimer;
public:
	QuadsLayer(std::shared_ptr<Light::Camera> camera);

	void OnAttach() override;
	void OnDetatch() override;
	
	void OnUpdate(float DeltaTime) override;
	void OnRender() override;

	void ShowDebugWindow() override;

	void OnEvent(Light::Event& event) override;
private:
	bool OnButtonPress  (Light::MouseButtonPressedEvent& event );
	bool OnButtonRelease(Light::MouseButtonReleasedEvent& event);
};