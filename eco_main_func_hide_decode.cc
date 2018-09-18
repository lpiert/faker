
ECO_NS_BEGIN(eco);
////////////////////////////////////////////////////////////////////////////////
class ECO_API App : public HeapOperators
{
	ECO_IMPL_API(); 
	ECO_NONCOPYABLE(App); 
public:
	virtual ~App();
private:
	friend class Startup; //访问App的私有和受保护的成员
	// set initiatiate
	static void set_app(IN App& app); // 初始化App

	// will first called by c++ raw main.
	static int  main(IN App& app, IN int argc, IN char* argv[]);

	// app life cycle managed by other app.
	static void init(IN App& app, bool command);
	static void exit(IN App& app);
};


////////////////////////////////////////////////////////////////////////////////
class Startup
{
public:
	// app main mode
	typedef int (*CMainFunc)(int argc, char* argv[]);
	inline Startup(IN App& app, IN CMainFunc main_func)
	{
		App::set_app(app);
		main_func = nullptr;
	}

	inline static int main(IN int argc, IN char* argv[])
	{
		return App::main(*eco::App::app(), argc, argv); 
	}

public:
	// dll mode
	inline Startup(IN App& app)
	{
		App::set_app(app);
		eco::App::init(app, false);
	}

	inline static void exit(IN App& app)
	{
		eco::App::exit(app);
	}
};
ECO_NS_END(eco);


////////////////////////////////////////////////////////////////////////////////
template<typename T, typename MainT>
T main(T argc, char* argv[])
{
	return MainT::main(argc, argv);
}
/*@ eco app declare: implement a app instance.*/
#define ECO_APP(AppClass, AppGet)\
ECO_NAME(AppClass, AppGet)\
const eco::Startup eco_startup(AppGet(), &main<int, eco::Startup>)



.............................................................................................................


ECO 主函数隐藏解析

宏解析：
		ECO_API :
#ifndef ECO_API
#	ifdef ECO_EXPORT
#		define ECO_API  __declspec(dllexport)
#	else
#		define ECO_API  __declspec(dllimport)
#	endif
#endif
/*
用于导出dll
		ECO_NONCOPYABLE:
*/


#define ECO_IMPL_API() \
public:\
	friend class Impl;\
	class Impl;\
	inline Impl& impl();\
	inline const Impl& impl() const;\
protected:\
	Impl* m_impl;
/*
间接开放，友元类 作为受保护的成员，但提供了获取方法。

*/



	ECO_NONCOPYABLE:
#define ECO_NONCOPYABLE(object_t) \
private:\
	object_t(IN const object_t& );\
	object_t& operator=(IN const object_t& );
/*
去除拷贝功能
*/


	ECO_NS_BEGIN:
	ECO_NS_END:
#define ECO_NS_BEGIN(ns) namespace ns{
#define ECO_NS_END(ns) }
/*
命名空间拆分

*/


	EC0_NAME:
#define ECO_NAME(object_t, method)\
inline object_t& method()\
{\
	static object_t s_object;\
	return s_object;\
}

/*
定义一个宏 传入类名 和 函数名字
返回一个 函数： auto func = ()->object& {
	static object static_object;
	return static_object;
}
*/


如何隐藏主函数呢？
///////////////////////////////////////////////////////////////////////////////////////////////////
	/*@ eco app declare: implement a app instance.*/
	#define ECO_APP(AppClass, AppGet)\
	ECO_NAME(AppClass, AppGet)\
	const eco::Startup eco_startup(AppGet(), &main<int, eco::Startup>)
///////////////////////////////////////////////////////////////////////////////////////////////////
	只要继承自App 的类，使用 宏 EC0_APP(class_name,class_get_func); // 传入类名和获取该类实列的方法名字
	1 . 定义一个方法，获取class_static_object;
	2 . 构造一个Startup 对象 
	Startup(IN App& app, IN CMainFunc main_func)
	{
		App::set_app(app); // 初始化App_s_object
		main_func = nullptr;
	}
	App& AppGet()
	{
		static App app;
		return app;
	}
	&main<int, eco::Startup> -->CMainFunc <-- typedef int (*CMainFunc)(int argc, char* argv[]);
	// int (*func)(int,char**); 函数指针 
	// typdef int (*func) (int,char**); 定义指针 func 为一种类型， 返回值int 参数(int ,char**)
	// func c_func; 这样 一种新类型就可以定义变量使用了

	Startup 构造函数里面 (App& app,CmainFunc main_func)--->(app, &main<int, eco::Startup>)

	main_func -->&main<int, eco::Startup>-->构造一个函数指针，& main,
	main<int,eco::Startup>-->调用模板
	template<typename T, typename MainT>
T main(T argc, char* argv[])
{
	return MainT::main(argc, argv);
}

int main(int argc,char**argv)
{
	return eco::Startup::main(argc,argv);// 返回下面的static_main_func
	/*
	eco::Startup::static int main(IN int argc, IN char* argv[])
	{
		return App::main(*eco::App::app(), argc, argv); // 返回下面 main_func
		/*
		*eco::App::app()-->
		/*
			App* App::app()	return s_app;
			void App::set_app(IN App& app) if (s_app == nullptr) s_app = &app; 
		*/
	//	App::static int  main(IN App& app, IN int argc, IN char* argv[]);
		/*
			int App::main(IN App& app, IN int argc, IN char* argv[])
			{
				eco::this_thread::init();

				// create dump file.
				#ifdef WIN32
					eco::win::Dump::init();
				#endif

				// init main parameters.
				for (int i = 0; i < argc; ++i)
				{
					std::string param(argv[i]);
					s_params.push_back(param);
				}

				App::init(app, true);
				app.impl().join_command();
				App::exit(app);
				return 0;
			}
		*/


		*/
	}
	*/
}

*/