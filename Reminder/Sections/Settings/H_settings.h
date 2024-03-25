#include <string>

namespace Reminder
{
	class WindowSpecs
	{
	private:
		std::string Title;
		unsigned int Width;
		unsigned int Height;
        unsigned int FPS;

    public:
        WindowSpecs():
            Title("Reminder"),
            Width(1920),
            Height(1080),
            FPS(120){}

        void setTitle(const std::string& title) 
        {
            Title = title;
        }

        void setSize(unsigned int width, unsigned int height) 
        {
            Width = width;
            Height = height;
        }

        void setFPS(unsigned int fps)
        {
            FPS = fps;
        }

        const std::string& getTitle() const 
        {
            return Title;
        }

        unsigned int getWidth() const 
        {
            return Width;
        }

        unsigned int getHeight() const 
        {
            return Height;
        }

        unsigned int getFPS() const
        {
            return FPS;
        }
	};

}