 #include <iostream>
 #include <string>
 using namespace std;
 class Texture {
 private:
    string* gpuData;  
    size_t size;      
 public:
    
    Texture(const string& file, size_t dataSize) : size(dataSize) {
        gpuData = new string("Texture loaded from: " + file);
        cout << "Texture created from " << file << " (" << size << " KB)" << endl;
    }
    
    ~Texture() {
        delete gpuData;
        cout << "Texture resource released." << endl;
    }
    
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    
    Texture(Texture&& other) noexcept : gpuData(other.gpuData), size(other.size) {
        other.gpuData = nullptr;
        other.size = 0;
        cout << "Move constructor: ownership transferred." << endl;
    }
    
    Texture& operator=(Texture&& other) noexcept {
        if (this != &other) {
            delete gpuData;  
            gpuData = other.gpuData;
            size = other.size;
            other.gpuData = nullptr;
            other.size = 0;
            cout << "Move assignment: ownership transferred." << endl;
        }
        return *this;
    }
    
    void display() const {
        if (gpuData)
            cout << *gpuData << " [Size: " << size << " KB]" << endl;
        else
            cout << "No texture data loaded." << endl;
    }
 };
 int main() {
    
    Texture tex1("brick_wall.png", 1024);
    tex1.display();
    
    Texture tex2 = std::move(tex1);
    tex2.display();
    tex1.display(); 
    
    Texture tex3("temp.png", 256);
    tex3 = std::move(tex2);
    tex3.display();
    tex2.display(); 
    return 0;
 }
