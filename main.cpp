#include "main.h"

rc::Camera cam = rc::Camera();
rc::Label desc{};

RkBody r({ 512 - 100, 0 }, 6.0f, { 0, 5000 }, 10.0f);
EulerBody e({ 512 - 80, 0 }, 6.0f, { 0, 5000 }, 10.0f);
SemiEulerBody s({ 512 - 60, 0 }, 6.0f, { 0, 5000 }, 10.0f);
MidpointBody m({ 512 - 40, 0 }, 6.0f, { 0, 5000 }, 10.0f);
LeapfrogBody l ({ 512 - 20, 0 }, 6.0f, { 0, 5000 }, 10.0f);
VerletBody v ({ 512, 0 }, 6.0f, { 0, 5000 }, 10.0f);

void process(double delta, rc::FrameEvent event) {
	r.Update(delta);
	e.Update(delta);
	s.Update(delta);
	m.Update(delta);
	l.Update(delta);
	v.Update(delta);
}

void draw() {
	desc.draw(cam);
	r.Draw(cam);
	e.Draw(cam);
	s.Draw(cam);
	m.Draw(cam);
	l.Draw(cam);
	v.Draw(cam);
}

int main(int argc, char* argv[]) {
	rc::init_window("Physics", rc::vec2(448, 240), rc::vec2(1024, 600));
	desc.align_mode = rc::LabelAlignMode::Begin;
	desc.size = rc::vec2(1024, 600);
	desc.font_color = rc::color(1, 1, 1, 1);
	desc.load(L"Runge-Kutta = Green\nEuler = Red\nSemi-Implicit Euler = Pink\nMidpoint = White\nLeapFrog = Blue\nVerlet = Yellow", "C:\\Windows\\Fonts\\arial.ttf");
	rc::register_process_func(process, draw);
	rc::set_background_color({ 0, 0, 0, 1 });
	rc::start_main_loop();
	rc::uninit_window();
}
