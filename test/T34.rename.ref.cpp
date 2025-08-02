// File: T34_rename.cpp
#include <T34.rename.hpp> // MyCppStruct
#include <T34.rename.hpp> // MyOtherCppStruct
#include <T34.rename.hpp> // MySecondStruct
#include <T34.rename.hpp> // NumericalClass
#include <T34.rename.hpp> // my_other_cpp_func
#include <T34.rename.hpp> // my_weird_cpp_func
#include <T34.rename.hpp> // tagged_cpp_function
#include <T34.rename.hpp> // tagged_function
#include <iterator> // __gnu_cxx::__normal_iterator
#include <memory> // std::allocator
#include <sstream> // __str__
#include <string> // std::basic_string
#include <string> // std::char_traits

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>, false)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*, false)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_T34_rename(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// my_weird_cpp_func(int) file:T34.rename.hpp line:
	M("").def("my_weird_python_func", (void (*)(int)) &my_weird_cpp_func, "C++: my_weird_cpp_func(int) --> void", pybind11::arg(""));

	// my_weird_cpp_func(std::string) file:T34.rename.hpp line:
	M("").def("my_weird_python_func", (void (*)(std::string)) &my_weird_cpp_func, "C++: my_weird_cpp_func(std::string) --> void", pybind11::arg(""));

	// my_other_cpp_func(int) file:T34.rename.hpp line:
	M("").def("my_other_python_func", (void (*)(int)) &my_other_cpp_func, "C++: my_other_cpp_func(int) --> void", pybind11::arg(""));

	// my_other_cpp_func(std::string) file:T34.rename.hpp line:
	M("").def("my_other_cpp_func", (void (*)(std::string)) &my_other_cpp_func, "C++: my_other_cpp_func(std::string) --> void", pybind11::arg(""));

	{ // MyCppStruct file:T34.rename.hpp line:
		pybind11::class_<MyCppStruct, std::shared_ptr<MyCppStruct>> cl(M(""), "MyPythonStruct", "");
		cl.def( pybind11::init( [](){ return new MyCppStruct(); } ) );
		cl.def("some_func", (void (MyCppStruct::*)() const) &MyCppStruct::some_func, "C++: MyCppStruct::some_func() const --> void");
	}
	{ // MySecondStruct file:T34.rename.hpp line:
		pybind11::class_<MySecondStruct, std::shared_ptr<MySecondStruct>> cl(M(""), "MySecondStruct", "");
		cl.def( pybind11::init( [](){ return new MySecondStruct(); } ) );
		cl.def("my_python_func", (void (MySecondStruct::*)() const) &MySecondStruct::my_cpp_func, "C++: MySecondStruct::my_cpp_func() const --> void");
	}
	{ // MyOtherCppStruct file:T34.rename.hpp line:
		pybind11::class_<MyOtherCppStruct, std::shared_ptr<MyOtherCppStruct>> cl(M(""), "MyOtherPythonStruct", "");
		cl.def( pybind11::init( [](){ return new MyOtherCppStruct(); } ) );
		cl.def("some_weird_python_func", (void (MyOtherCppStruct::*)(int)) &MyOtherCppStruct::some_weird_cpp_func, "C++: MyOtherCppStruct::some_weird_cpp_func(int) --> void", pybind11::arg(""));
		cl.def("some_weird_python_func", (void (MyOtherCppStruct::*)(std::string)) &MyOtherCppStruct::some_weird_cpp_func, "C++: MyOtherCppStruct::some_weird_cpp_func(std::string) --> void", pybind11::arg(""));
		cl.def("some_other_python_func", (void (MyOtherCppStruct::*)(int)) &MyOtherCppStruct::some_other_cpp_func, "C++: MyOtherCppStruct::some_other_cpp_func(int) --> void", pybind11::arg(""));
		cl.def("some_other_cpp_func", (void (MyOtherCppStruct::*)(std::string)) &MyOtherCppStruct::some_other_cpp_func, "C++: MyOtherCppStruct::some_other_cpp_func(std::string) --> void", pybind11::arg(""));
	}
	// tagged_function() file:T34.rename.hpp line:
	M("").def("tagged_function_int", (int (*)()) &tagged_function<int>, "C++: tagged_function() --> int");

	// tagged_function() file:T34.rename.hpp line:
	M("").def("tagged_function_str", (std::string (*)()) &tagged_function<std::string>, "C++: tagged_function() --> std::string");

	// tagged_cpp_function() file:T34.rename.hpp line:
	M("").def("tagged_python_function", (int (*)()) &tagged_cpp_function<int>, "C++: tagged_cpp_function() --> int");

	// tagged_cpp_function() file:T34.rename.hpp line:
	M("").def("tagged_python_function", (std::string (*)()) &tagged_cpp_function<std::string>, "C++: tagged_cpp_function() --> std::string");

	{ // NumericalClass file:T34.rename.hpp line:
		pybind11::class_<NumericalClass<unsigned char>, std::shared_ptr<NumericalClass<unsigned char>>> cl(M(""), "NumericalClass_uint8_t", "");
		cl.def( pybind11::init( [](){ return new NumericalClass<unsigned char>(); } ) );
	}
	{ // NumericalClass file:T34.rename.hpp line:
		pybind11::class_<NumericalClass<unsigned short>, std::shared_ptr<NumericalClass<unsigned short>>> cl(M(""), "NumericalClass_uint16_t", "");
		cl.def( pybind11::init( [](){ return new NumericalClass<unsigned short>(); } ) );
	}
	{ // NumericalClass file:T34.rename.hpp line:
		pybind11::class_<NumericalClass<unsigned int>, std::shared_ptr<NumericalClass<unsigned int>>> cl(M(""), "NumericalClass_uint32_t", "");
		cl.def( pybind11::init( [](){ return new NumericalClass<unsigned int>(); } ) );
	}
	{ // NumericalClass file:T34.rename.hpp line:
		pybind11::class_<NumericalClass<unsigned long>, std::shared_ptr<NumericalClass<unsigned long>>> cl(M(""), "NumericalClass_uint64_t", "");
		cl.def( pybind11::init( [](){ return new NumericalClass<unsigned long>(); } ) );
	}
}


// File: T34_rename_1.cpp
#include <T34.rename.hpp> // foo::bar::Tag
#include <T34.rename.hpp> // foo::bar::TaggedClass
#include <sstream> // __str__

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>, false)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*, false)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_T34_rename_1(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // foo::bar::Tag file:T34.rename.hpp line:
		pybind11::class_<foo::bar::Tag, std::shared_ptr<foo::bar::Tag>> cl(M("foo::bar"), "Tag", "");
		cl.def( pybind11::init( [](){ return new foo::bar::Tag(); } ) );
		cl.def( pybind11::init( [](foo::bar::Tag const &o){ return new foo::bar::Tag(o); } ) );
	}
	{ // foo::bar::TaggedClass file:T34.rename.hpp line:
		pybind11::class_<foo::bar::TaggedClass<foo::bar::Tag>, std::shared_ptr<foo::bar::TaggedClass<foo::bar::Tag>>> cl(M("foo::bar"), "TaggedClass_Tag", "");
		cl.def( pybind11::init( [](){ return new foo::bar::TaggedClass<foo::bar::Tag>(); } ) );
		cl.def("get_tag", (struct foo::bar::Tag (foo::bar::TaggedClass<foo::bar::Tag>::*)() const) &foo::bar::TaggedClass<foo::bar::Tag>::get_tag, "C++: foo::bar::TaggedClass<foo::bar::Tag>::get_tag() const --> struct foo::bar::Tag");
		cl.def("another_python_func", (void (foo::bar::TaggedClass<foo::bar::Tag>::*)() const) &foo::bar::TaggedClass<foo::bar::Tag>::another_cpp_func, "C++: foo::bar::TaggedClass<foo::bar::Tag>::another_cpp_func() const --> void");
	}
}


#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include <pybind11/pybind11.h>

using ModuleGetter = std::function< pybind11::module & (std::string const &) >;

void bind_T34_rename(std::function< pybind11::module &(std::string const &namespace_) > &M);
void bind_T34_rename_1(std::function< pybind11::module &(std::string const &namespace_) > &M);


PYBIND11_MODULE(T34_rename, root_module) {
	root_module.doc() = "T34_rename module";

	std::map <std::string, pybind11::module> modules;
	ModuleGetter M = [&](std::string const &namespace_) -> pybind11::module & {
		auto it = modules.find(namespace_);
		if( it == modules.end() ) throw std::runtime_error("Attempt to access pybind11::module for namespace " + namespace_ + " before it was created!!!");
		return it->second;
	};

	modules[""] = root_module;

	static std::vector<std::string> const reserved_python_words {"nonlocal", "global", };

	auto mangle_namespace_name(
		[](std::string const &ns) -> std::string {
			if ( std::find(reserved_python_words.begin(), reserved_python_words.end(), ns) == reserved_python_words.end() ) return ns;
			return ns+'_';
		}
	);

	std::vector< std::pair<std::string, std::string> > sub_modules {
		{"", "foo"},
		{"foo", "bar"},
	};
	for(auto &p : sub_modules ) modules[ p.first.empty() ? p.second :  p.first+"::"+p.second ] = modules[p.first].def_submodule( mangle_namespace_name(p.second).c_str(), ("Bindings for " + p.first + "::" + p.second + " namespace").c_str() );

	//pybind11::class_<std::shared_ptr<void>>(M(""), "_encapsulated_data_");

	bind_T34_rename(M);
	bind_T34_rename_1(M);

}

// Source list file: TEST/T34_rename.sources
// T34_rename.cpp
// T34_rename.cpp
// T34_rename_1.cpp

// Modules list file: TEST/T34_rename.modules
// foo foo.bar 
