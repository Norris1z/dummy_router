#include <string>
#include <functional>
#include <map>

class Router{
private:
  std::map<std::string,std::function<void(std::string)>> get_routes;
  std::map<std::string,std::function<void(std::string)>> post_routes;
  
public:
  Router() = default;
  Router(const Router&) = delete;
  Router(const Router&&) = delete;
  Router& operator = (const Router&) = delete;
  Router& operator = (const Router&&) = delete;
  
  template<typename Url,typename Callback>
  void get(const Url& url,const Callback& callback)
  {
    get_routes[url] = callback;
  }
  
  template<typename Url,typename Callback>
  void post(const Url& url,const Callback& callback)
  {
    post_routes[url] = callback;
  }
 
  void mapGetRoutes(const char* url)
  {
  	for(std::map<std::string,std::function<void(std::string)>>::iterator it= get_routes.begin(); it!=get_routes.end();it++)
    {
     	if(it->first == url){
        	std::invoke(it->second,it->first);
        }
    }
  }
  void mapPostRoutes(const char* url)
  {
  	for(std::map<std::string,std::function<void(std::string)>>::iterator it= post_routes.begin(); it!=post_routes.end();it++)
    {
     	if(it->first == url){
        	std::invoke(it->second,it->first);
        }
    }
  }
  bool routeExists(const char*url)
  {
    for(std::map<std::string,std::function<void(std::string)>>::iterator it= post_routes.begin(); it!=post_routes.end();it++)
    {
     	if(it->first == url){
        	return true;
        }
    }
    for(std::map<std::string,std::function<void(std::string)>>::iterator it= get_routes.begin(); it!=get_routes.end();it++)
    {
     	if(it->first == url){
        	return true;
        }
    }
    return false;
  }
  
  void dispatch(const char* url)
  {
   	if(routeExists(url))
    {
      mapGetRoutes(url);
      mapPostRoutes(url);
    }else
    {
      throw std::runtime_error(std::string("Route not found --- ").append(url));
    }
  }
  
}router;

struct HomeController{
void getUserHome(){}
void login(){}
}homeController;

int main([[maybe_unused]] int argc,[[maybe_unused]]const char* argv[])
{
	router.get("/home",[&]([[maybe_unused]]std::string url){
      return std::invoke(&HomeController::getUserHome,homeController);
    });
  	router.post("/login",[&]([[maybe_unused]]std::string url){
    	return std::invoke(&HomeController::login,homeController);
    });
   router.dispatch(argv[1]);
}
