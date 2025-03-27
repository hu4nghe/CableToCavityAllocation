#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>

struct Cavity
{
    int CavityGauge = 0;
    std::pair<double,double> RelativePos;
    Cavity(float x,float y) : RelativePos(x,y), CavityGauge(0){}
};


std::vector<Cavity> GenerateCavityRelativePos() 
{
    std::vector<Cavity> Cavities;
    
    int top = 17;
    int middle = 16;
    int bottom = 17;
     
    auto distribute_x = [](int NumCavity, float shift) 
    {
        std::vector<float> XPos;
        float step = (2 - 2*shift) / (NumCavity - 1);
        for (int i = 0; i < NumCavity; i++) 
        {
            XPos.push_back(-1 + i * step + shift);
        }
        return XPos;
    };

    std::vector<float> x_top    = distribute_x(top,     0.0f);
    std::vector<float> x_middle = distribute_x(middle,  0.0625f);
    std::vector<float> x_bottom = distribute_x(bottom,  0.0f);

    for (float x : x_top)    Cavities.push_back({x,  1.0f});
    for (float x : x_middle) Cavities.push_back({x,  0.0f});
    for (float x : x_bottom) Cavities.push_back({x, -1.0f});

    return Cavities;
}

int main() 
{
    auto res = GenerateCavityRelativePos();
    int count = 1;
    for(auto& point : res)
    {
        std::cout<<count<<":{"<<point.RelativePos.first<<","<<point.RelativePos.second<<"}\n";
        count++;
    }
    return 0;
}
