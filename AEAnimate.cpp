#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"
#include "Fish.h"
#include "Seaweed.h"


emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    // grid width and height
    const int num_h_boxes = 30;
    const int num_w_boxes = 30;
    const double RECT_SIDE = 8;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};
    //create a canvas
    emp::web::Canvas canvas{width, height, "canvas"};

    private:
        emp::Random random{2};
        OrgWorld world{random};


    public:
    
    /* Constructor: initializes canvas, control buttons, and cell grid with random values */
    AEAnimator() {
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        world.Resize(num_w_boxes, num_h_boxes);
        randomStart();
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
    }  

    void randomStart(){
        for (int i = 0; i < num_w_boxes * num_h_boxes; i++) {
            if (random.GetDouble() < 0.3) {
                world.AddOrgAt(new Seaweed(&random), i);
            } else if (random.GetDouble() < 0.1) {
                world.AddOrgAt(new Fish(&random, 800), i); //start the goats with 1000 points to give it a chance to survive
            }
        }
    }

    /* Called on each frame: draws current state and applies AE update rule */
    void DoFrame() override {
        canvas.Clear();
        world.Update();
        DrawGrid();
    }

    private:
    void DrawGrid(){
        int PosOrg = 0;
        for (int x = 0; x < num_h_boxes; x++){
            for (int y = 0; y < num_w_boxes; y++) {
                if (world.IsOccupied(PosOrg)) {
                    if (world.GetOrg(PosOrg).GetSpeciesType() == 1){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "green");
                    } else if (world.GetOrg(PosOrg).GetSpeciesType() == 2) {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "blue", "blue");
                } }
                else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                }
                PosOrg++;
        }
    }
}
};

AEAnimator animator;

int main() {animator.Step();}