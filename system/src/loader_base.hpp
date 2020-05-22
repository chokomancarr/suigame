
/*
 * Generated by ChokoEditor.
 * DO NOT EDIT.
 */
#pragma once
#include "chokoplayer.hpp"

CE_BEGIN_PL_NAMESPACE

CE_PL_OBJ(ScrLdImpl_Texx)

CE_PL_OBJ(ScriptLoaderImpl)
class _ScriptLoaderImpl : public _ScriptLoaderBase {
protected:
	const std::string _sig;
	const std::vector<ScriptVarEntry> _entries;
	Component tar;
	std::unordered_map<std::string, ScriptLoaderImpl> _lds;

	ScriptLoaderImpl getld(const std::string& s);

	_ScriptLoaderImpl(const std::string& s, const std::vector<ScriptVarEntry>& e)
		: _sig(s), _entries(e) {}
public:
	static void Init() {
		instance = std::make_shared<_ScriptLoaderImpl>();
	}
	_ScriptLoaderImpl() : _sig(""), _entries({}), tar(nullptr), _lds({}) {}
	CE_PL_NS ScriptLoaderBase GetLoaderOf(const std::string& s) override {
		return getld(s);
	}
	std::string sig() override {
		return _sig;
	}
	Component Instantiate() override { abort(); }
	void activeTarget(const Component& t) override {
		tar = t;
	}
	std::vector<ScriptVarEntry> GetVarsOf(const std::string& s) override {
		return getld(s)->_entries;
	}
#define _IMPL_GETSET(tp)\
    void set_ ## tp(const std::string&, const tp&) override { abort(); }\
    tp get_ ## tp(const std::string&) override { abort(); };

    _IMPL_GETSET(int)
    _IMPL_GETSET(float)
    _IMPL_GETSET(Vec2)
    _IMPL_GETSET(Vec3)
    _IMPL_GETSET(Vec4)
    _IMPL_GETSET(Quat)
    _IMPL_GETSET(Asset)
#undef _IMPL_GETSET
};

CE_END_PL_NAMESPACE

#include "loaders/load_Texx.hpp"
