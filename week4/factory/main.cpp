#include <iostream>
#include <vector>
#include <string>

class Content{  // Product (abstract)
public:
    Content() {}
    virtual ~Content() {}
    virtual std::string getEncoding() = 0;// pure virtual method
};

class Image : public Content { // Concrete Product
public:
    std::string getEncoding() override {
        return "png";
    }
};
class Text : public Content { // Concrete Product
public:
    std::string getEncoding() override {
        return "ascii";
    }
};

class Application{ // Framework (abstract)
public:
    Application() {}
    virtual ~Application() { }
    virtual Content *getContent() = 0; // pure virtual
    virtual std::string getAppType()
    {
        return "boring app";
    }
};

class TextDocument: public Application { // Application one
    Content *getContent() override {
        return new Text();
    }
    std::string getAppType()
    {
        return "text document";
    }
};

class ImageEditor: public Application { // Application two
    Content *getContent() override {
        return new Image();
    }
    std::string getAppType()
    {
        return "image editor";
    }
};

int main() {

    // Create 2 new applications. These will call the default constructor from the Application class.
    Application * myFirstTextDocument = new TextDocument();
    Application * paintDotNet = new ImageEditor();

    // Store these two in a list. push_back will append to the list
    std::vector<Application *> applications;
    applications.push_back(myFirstTextDocument);
    applications.push_back(paintDotNet);

    // For each application in the list of applications we just made
    for(Application * app : applications)
    {

        // Print out information about it
        Content* content = app->getContent();
        std::cout <<app->getAppType() << "'s content has " << content->getEncoding() << " encoding" << std::endl;
        delete content;
    }
    return 0;
}
