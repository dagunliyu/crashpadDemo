
//https://blog.csdn.net/weixin_42887343/article/details/129324679

template <typename F>
class ScopeGuard
{
public:
	explicit ScopeGuard(F&& f) : m_func(std::move(f)), m_dismiss(false) {}
	explicit ScopeGuard(const F& f) : m_func(f), m_dismiss(false) {}
	ScopeGuard(ScopeGuard&& rhs)
		: m_func(std::move(rhs.m_func))
		, m_dismiss(rhs.m_dismiss)
	{
		rhs.Dismiss();
	}

	~ScopeGuard()
	{
		if (!m_dismiss)
			m_func();
	}

	void Dismiss()
	{
		m_dismiss = true;
	}

private:
	F m_func;
	bool m_dismiss;

	ScopeGuard();
	ScopeGuard(const ScopeGuard&);
	ScopeGuard& operator=(const ScopeGuard&);
};
