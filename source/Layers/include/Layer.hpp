#pragma once


#include <memory>

#include <Event.hpp>

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnEvent(Event& event) {}

	virtual void OnUpdate() {}
	virtual void OnRender() {}

	template<std::derived_from<Layer> T, typename... Args>
	void TransitionTo(Args&&... args)
	{
		QueueTransition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
	}

	bool IsActive() const { return m_Active; }
	void SetActive(bool active) { m_Active = active; }
	bool IsUi() const { return m_IsUi; }
	void SetUi(bool isUi_) { m_IsUi = isUi_; }

private:

	bool m_Active = true;
	bool m_IsUi = false;

	void QueueTransition(std::unique_ptr<Layer> layer);
};

