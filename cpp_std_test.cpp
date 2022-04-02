#include <string>
#include <iostream>
#include <memory>
#include <limits>
#include <cstdint>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iterator>

class D;

struct StructType
{
int i_val;
double d_val;
std::string s_val;

StructType(std::string s)
{
s_val = s;
}

StructType(const StructType& s)
{
i_val = s.i_val;
d_val = s.d_val;
s_val = s.s_val;
}
};

class A
{
public:
    A(const std::string& s):
        s_(s),
        p_d_(nullptr)
    {
        std::cout << "construct: " << s_ << std::endl;
    }
    ~A()
    {
        std::cout << "destruct: " << s_ << std::endl;
    }
    void show()
    {
        std::cout << "hi, I am " << s_ << std::endl;
    }

    std::string s_;
    std::shared_ptr<D> p_d_;
};

class B
{
public:
    B():
        //ax("ax"),
        a(new A("a")),
        ay(nullptr)
    {
        a->show();
        ay->show();
    }

    ~B()
    {
       std::cout << "destruct B..." << std::endl;
    }
private:
    //A ax;
    std::unique_ptr<A> a;
    std::unique_ptr<A> ay;
};


class MapInfo
{
    private:
        double x_size_;  // map size in x axis, unit: m
        double y_size_;  // map size in y axis, unit: m
        double step_size_;
        std::int32_t x_grid_size_;     // grids count in x axis
        std::int32_t y_grid_size_;     // grids count in y axis
        double offset_x_;
        double offset_y_;

    public:
        MapInfo(const double &x, 
                const double &y, 
                const double &step,
                const double &offset_x = 0.0,
                const double &offset_y = 0.0) : x_size_(x),
                                                y_size_(y),
                                                step_size_(step),
                                                x_grid_size_(std::numeric_limits<std::int32_t>::max()),
                                                y_grid_size_(std::numeric_limits<std::int32_t>::max()),
                                                offset_x_(offset_x),
                                                offset_y_(offset_y)
        {
            if (step < std::numeric_limits<double>::epsilon())
            {
                return;
            }

            x_grid_size_ = int(x_size_ / step_size_) + 1;
            y_grid_size_ = int(y_size_ / step_size_) + 1;
        }

        const double GetStepSize() const { return step_size_; }
        const double GetMapSizeX() const { return x_size_; }
        const double GetMapSizeY() const { return y_size_; }

        const double GetX(const std::int32_t &grid_x) const { return grid_x * step_size_ - offset_x_; }
        const double GetY(const std::int32_t &grid_y) const { return grid_y * step_size_ - offset_y_; }

        const std::int32_t GetGridSizeX() const { return x_grid_size_; }
        const std::int32_t GetGridSizeY() const { return y_grid_size_; }
        const std::int32_t GetGridX(const double &x) const { return std::int32_t(round((x + offset_x_) / step_size_)); }
        const std::int32_t GetGridY(const double &y) const { return std::int32_t(round((y + offset_y_) / step_size_)); }

        const double GetOffsetX() const { return offset_x_; }
        const double GetOffsetY() const { return offset_y_; }


        bool SetOrigin(const double &offset_x, const double &offset_y)
        {
            offset_x_ = offset_x;
            offset_y_ = offset_y;

            return true;
        }
};
class D
{
public:
D(){}
~D(){};
};

namespace ns1
{
   struct Type1
   {
      std::vector<int> v;
      double dval;
      std::string sval;
   };
}


namespace ns2
{
   struct Type1
   {
      std::vector<int> v;
      double dval;
      std::string sval;
   };
}

void my_function(const std::uint32_t& cnt = 100)
{
    for(auto i = 0; i < cnt; ++i)
    {
       //
    }
    std::cout << cnt << " times this function run..." << std::endl;
} 

int main(int argc, char** argv)
{
    std::string s{"base_link"};
    std::cout << "s type: std::string" << std::endl
         << s << std::endl
         << "s.compare(\"base_link\"): " << s.compare("base_link") << std::endl
         << "s == \"base_link\": " << std::to_string(s == "base_link") << std::endl
         << "\"base_link\" == s: " << std::to_string("base_link" == s) << std::endl
         << "s.contains(\"base_link\")" << ("base_link" == s) << std::endl;
         
         
      std::string cube_1{"cube_1_link"}; 
      std::string obj_name {cube_1.substr(0, cube_1.rfind("_", 0))};
      std::cout << "obj_name: " << obj_name << std::endl
                << "\t obj_name2: " << cube_1.substr(0, cube_1.rfind("_")) << std::endl;
          
     //B b;     
         
         
     MapInfo map_a(100.0, 200.0, 0.1, 50.0, 100.0);
     
     std::cout << "grid_x (for 50.0): " << map_a.GetGridX(50.0) << std::endl
               << "grid_y (for 100.0): " << map_a.GetGridY(100.0) << std::endl;
               
     MapInfo map_b(map_a);
     map_b.SetOrigin(0,0);
     std::cout << "grid_x (for 50.0): " << map_b.GetGridX(50.0) << std::endl
               << "grid_y (for 100.0): " << map_b.GetGridY(100.0) << std::endl
               << "x(for grid_x := 60): " << map_b.GetX(60) << std::endl
               << "y(for grid_y := 100): " << map_b.GetY(map_b.GetGridY(100.0)) << std::endl;
         
         
    std::vector<std::string> joint_names{"waist", "shoulder", "elbow", "wrist1", "wrist2", "wrist3"};
         
         
    std::unordered_map<std::string, std::uint32_t> joint_name_index;
    std::uint32_t i = 0;
    std::for_each(joint_names.cbegin(),
                  joint_names.cend(),
                  [&](const auto &joint_name)
                  { joint_name_index.emplace(joint_name, i++); });
                  
                  
     std::for_each(joint_name_index.cbegin(), joint_name_index.cend(), 
        [](auto& joint_idx){std::cout << "joint: " << joint_idx.first << ", index: " << joint_idx.second << std::endl;});
        
        
     my_function();
     my_function(200);
     
     
     std::ostream_iterator<double> os_it(std::cout, ", ");
     std::vector<double> v1{1.0,2.0, 3.0, 4.0, 5.0};
     std::copy(v1.cbegin(), v1.cend(), os_it);
     
     std::cout << std::endl;
     std::vector<double> v2{v1.crbegin(), v1.crend()};
     std::copy(v2.cbegin(), v2.cend(), os_it);
     
     std::cout << "pi: " << M_PI << std::endl;

     std::shared_ptr<ns1::Type1> pns1t1 = std::make_shared<ns1::Type1>();

        StructType st("a");
        StructType st2(st);


     //return 0; 
}
