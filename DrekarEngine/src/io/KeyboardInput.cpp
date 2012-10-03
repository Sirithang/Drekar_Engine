#include "io/KeyboardInput.h"
#include <gl/glfw.h>


using namespace de::io;

KeyboardInput::KeyboardInput(const std::string& pName)
	: AInput(pName, "KeyboardInput")
{
	for(int i = 1; i < 256; i++)
	{
		char temp[2];
		temp[0] = (char)i;
		temp[1] = '\0';
		mAxis[std::string(temp)] = 0;
	}


	// TODO : Finish all special key handing
	std::string tempTab[] =
	{
		"esc",        
		"F1",        
		"F2",
		"F3",         
		"F4",         
		"F5",         
		"F6",         
		"F7",         
		"F8",         
		"F9",         
		"F10",        
		"F11",        
		"F12",               
		"up",         
		"down",       
		"left",       
		"right",      
		"lshift",     
		"rshift",     
		"lctrl",      
		"rctrl",      
		"lalt",       
		"ralt",       
		"tab",        
		"enter",      
		"back",  
		"insert",     
		"del",        
		"pageup"
	};
		/*GLFW_KEY_PAGEDOWN   
		GLFW_KEY_HOME       
		GLFW_KEY_END        
		GLFW_KEY_KP_0       
		GLFW_KEY_KP_1       
		GLFW_KEY_KP_2       
		GLFW_KEY_KP_3       
		GLFW_KEY_KP_4       
		GLFW_KEY_KP_5       
		GLFW_KEY_KP_6       
		GLFW_KEY_KP_7       
		GLFW_KEY_KP_8       
		GLFW_KEY_KP_9       
		GLFW_KEY_KP_DIVIDE  
		GLFW_KEY_KP_MULTIPLY
		GLFW_KEY_KP_SUBTRACT
		GLFW_KEY_KP_ADD     
		GLFW_KEY_KP_DECIMAL 
		GLFW_KEY_KP_EQUAL   
		GLFW_KEY_KP_ENTER   
		GLFW_KEY_KP_NUM_LOCK
		GLFW_KEY_CAPS_LOCK  
		GLFW_KEY_SCROLL_LOCK
		GLFW_KEY_PAUSE      
		GLFW_KEY_LSUPER     
		GLFW_KEY_RSUPER     
		GLFW_KEY_MENU       
		GLFW_KEY_LAST */      


	//----- enum

	int enumID[] = 
	{
		GLFW_KEY_ESC       
		,GLFW_KEY_F1         
		,GLFW_KEY_F2         
		,GLFW_KEY_F3         
		,GLFW_KEY_F4         
		,GLFW_KEY_F5         
		,GLFW_KEY_F6         
		,GLFW_KEY_F7         
		,GLFW_KEY_F8         
		,GLFW_KEY_F9         
		,GLFW_KEY_F10        
		,GLFW_KEY_F11        
		,GLFW_KEY_F12        
		,GLFW_KEY_F13        
		,GLFW_KEY_F14        
		,GLFW_KEY_F15        
		,GLFW_KEY_F16        
		,GLFW_KEY_F17        
		,GLFW_KEY_F18        
		,GLFW_KEY_F19        
		,GLFW_KEY_F20        
		,GLFW_KEY_F21        
		,GLFW_KEY_F22        
		,GLFW_KEY_F23        
		,GLFW_KEY_F24        
		,GLFW_KEY_F25        
		,GLFW_KEY_UP         
		,GLFW_KEY_DOWN       
		,GLFW_KEY_LEFT       
		,GLFW_KEY_RIGHT      
		,GLFW_KEY_LSHIFT     
		,GLFW_KEY_RSHIFT     
		,GLFW_KEY_LCTRL      
		,GLFW_KEY_RCTRL      
		,GLFW_KEY_LALT       
		,GLFW_KEY_RALT       
		,GLFW_KEY_TAB        
		,GLFW_KEY_ENTER      
		,GLFW_KEY_BACKSPACE  
		,GLFW_KEY_INSERT     
		,GLFW_KEY_DEL        
		,GLFW_KEY_PAGEUP
		/*GLFW_KEY_PAGEDOWN   
		GLFW_KEY_HOME       
		GLFW_KEY_END        
		GLFW_KEY_KP_0       
		GLFW_KEY_KP_1       
		GLFW_KEY_KP_2       
		GLFW_KEY_KP_3       
		GLFW_KEY_KP_4       
		GLFW_KEY_KP_5       
		GLFW_KEY_KP_6       
		GLFW_KEY_KP_7       
		GLFW_KEY_KP_8       
		GLFW_KEY_KP_9       
		GLFW_KEY_KP_DIVIDE  
		GLFW_KEY_KP_MULTIPLY
		GLFW_KEY_KP_SUBTRACT
		GLFW_KEY_KP_ADD     
		GLFW_KEY_KP_DECIMAL 
		GLFW_KEY_KP_EQUAL   
		GLFW_KEY_KP_ENTER   
		GLFW_KEY_KP_NUM_LOCK
		GLFW_KEY_CAPS_LOCK  
		GLFW_KEY_SCROLL_LOCK
		GLFW_KEY_PAUSE      
		GLFW_KEY_LSUPER     
		GLFW_KEY_RSUPER     
		GLFW_KEY_MENU       
		GLFW_KEY_LAST*/ 
	};
	
	int size = sizeof(tempTab) / sizeof(std::string);

	for(int i = 0; i < size; i++)
	{
		SpecialKey k;
		k.name = tempTab[i];
		k.ID = enumID[i];

		mAxis[k.name] = 0;
		mSpecialKeys.push_back(k);
	}
}

//-----------------------------------------------------

void KeyboardInput::update()
{
	for(int i = 1; i < 256; i++)
	{
		char temp[2];
		temp[0] = (char)i;
		temp[1] = '\0';

		if(glfwGetKey(i) == GLFW_PRESS)
		{
			mAxis[temp] = 1.0f;
		}
		else
		{
			mAxis[temp] = 0.0f;
		}
	}

	std::list<SpecialKey>::iterator it = mSpecialKeys.begin();
	while(it != mSpecialKeys.end())
	{
		if(glfwGetKey(it->ID) == GLFW_PRESS)
		{
			mAxis[it->name] = 1.0f;
		}
		else
		{
			mAxis[it->name] = 0.0f;
		}

		it++;
	}
}