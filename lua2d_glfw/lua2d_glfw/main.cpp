/*
 Copyright (c) 2015 chenbingfeng (iichenbf#gmail.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include <math.h>

#include <iostream>
#include <chrono>

#include "cppgl/cppgl.h"
#include "utils.h"
#include "lua2d.h"

extern "C" {

#include "lua53/lua.h"
#include "lua53/lauxlib.h"
#include "lua53/lualib.h"

}

#include "glfbx/glfbx.h"

static void lua2d_demo()
{
    auto& director = l2d::Director::getInstance();
    director.init(600, 600, "appName");

    auto scene = l2d::Scene::create();
    auto layer = l2d::Layer::create();
    auto arrow = l2d::ImageSprite::create("shooting_arrow.png",71, 98);
    arrow->load();

    auto cube = l2d::MeshSprite::create("cube.obj", "cube.png");
    cube->load();
    auto gaoda = l2d::MeshSprite::create("gaoda.obj", "gaoda.jpg");
    gaoda->load();

    auto tank = l2d::MeshSprite::create("tank.obj", "tank.jpg");
    tank->load();
    arrow->setX(0.5f);
    arrow->scale(1.5f);
    arrow->rotate(-45.0f);
    arrow->setZ(0.5f);
    cube->scale(1.2f);

//    layer->addSprite(cube);
//    layer->addSprite(arrow);
    layer->addSprite(gaoda);
//    layer->addSprite(tank);
    gaoda->setY(-20.0f);

    scene->addLayer(layer, 0);
    director.runWithScene(scene);
    director.setProj(glm::radians(45.0f), 800.0f/600.0f, 1.0f, 100000.0f);
    director.lookAt(glm::vec3(23.1f,80.0f,90.2f), glm::vec3(0.1f,0.1f, 0.0f), glm::vec3(0.0f,1.0f,0.0f));
    director.mainLoop();
}

int main(int argc, const char * argv[])
{
    std::cout << "hello world!" << std::endl;
//    cppgl::cppgl_test();
//    lua2d_demo();
    glFbxMain();
    return 0;
}