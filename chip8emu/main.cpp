#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "cpu.h"

class Emulator : public olc::PixelGameEngine
{
public:
	Emulator()
	{
		sAppName = "Chip8";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		chip8.init();
		if (!chip8.loadProgram("roms/INVADERS")) // This rom selection solution is not very good
			return false;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		for (int cycles = 0; cycles <= 8; cycles++)
			chip8.emulateCycle();


		/*
		Key Up
		*/
		if (GetKey(olc::Key::NP1).bReleased) {
			chip8.key[0x1] = 0; std::cout << "NP1" << std::endl;
		}
		else if (GetKey(olc::Key::NP2).bReleased) {
			chip8.key[0x2] = 0; std::cout << "NP2" << std::endl;
		}
		else if (GetKey(olc::Key::NP3).bReleased) {
			chip8.key[0x3] = 0; std::cout << "NP3" << std::endl;
		}
		else if (GetKey(olc::Key::NP4).bReleased) {
			chip8.key[0xC] = 0; std::cout << "NP4" << std::endl;
		}

		else if (GetKey(olc::Key::Q).bReleased) {
			chip8.key[0x4] = 0; std::cout << "Q" << std::endl;
		}
		else if (GetKey(olc::Key::W).bReleased) {
			chip8.key[0x5] = 0; std::cout << "W" << std::endl;
		}
		else if (GetKey(olc::Key::E).bReleased) {
			chip8.key[0x6] = 0; std::cout << "E" << std::endl;
		}
		else if (GetKey(olc::Key::R).bReleased) {
			chip8.key[0xD] = 0; std::cout << "R" << std::endl;
		}

		else if (GetKey(olc::Key::A).bReleased) {
			chip8.key[0x7] = 0; std::cout << "A" << std::endl;
		}
		else if (GetKey(olc::Key::S).bReleased) {
			chip8.key[0x8] = 0; std::cout << "S" << std::endl;
		}
		else if (GetKey(olc::Key::D).bReleased) {
			chip8.key[0x9] = 0; std::cout << "D" << std::endl;
		}
		else if (GetKey(olc::Key::F).bReleased) {
			chip8.key[0xE] = 0; std::cout << "F" << std::endl;
		}

		else if (GetKey(olc::Key::Z).bReleased) {
			chip8.key[0xA] = 0; std::cout << "Z" << std::endl;
		}
		else if (GetKey(olc::Key::X).bReleased) {
			chip8.key[0x0] = 0; std::cout << "X" << std::endl;
		}
		else if (GetKey(olc::Key::C).bReleased) {
			chip8.key[0xB] = 0; std::cout << "C" << std::endl;
		}
		else if (GetKey(olc::Key::V).bReleased) {
			chip8.key[0xF] = 0; std::cout << "V" << std::endl;
		}


		/*
		Key down
		*/
		if (GetKey(olc::Key::NP1).bPressed) {
			chip8.key[0x1] = 1; std::cout << "NP1" << std::endl;
		}
		else if (GetKey(olc::Key::NP2).bPressed) {
			chip8.key[0x2] = 1; std::cout << "NP2" << std::endl;
		}
		else if (GetKey(olc::Key::NP3).bPressed) {
			chip8.key[0x3] = 1; std::cout << "NP3" << std::endl;
		}
		else if (GetKey(olc::Key::NP4).bPressed) {
			chip8.key[0xC] = 1; std::cout << "NP4" << std::endl;
		}

		else if (GetKey(olc::Key::Q).bPressed) {
			chip8.key[0x4] = 1; std::cout << "Q" << std::endl;
		}
		else if (GetKey(olc::Key::W).bPressed) {
			chip8.key[0x5] = 1; std::cout << "W" << std::endl;
		}
		else if (GetKey(olc::Key::E).bPressed) {
			chip8.key[0x6] = 1; std::cout << "E" << std::endl;
		}
		else if (GetKey(olc::Key::R).bPressed) {
			chip8.key[0xD] = 1; std::cout << "R" << std::endl;
		}

		else if (GetKey(olc::Key::A).bPressed) {
			chip8.key[0x7] = 1; std::cout << "A" << std::endl;
		}
		else if (GetKey(olc::Key::S).bPressed) {
			chip8.key[0x8] = 1; std::cout << "S" << std::endl;
		}
		else if (GetKey(olc::Key::D).bPressed) {
			chip8.key[0x9] = 1; std::cout << "D" << std::endl;
		}
		else if (GetKey(olc::Key::F).bPressed) {
			chip8.key[0xE] = 1; std::cout << "F" << std::endl;
		}

		else if (GetKey(olc::Key::Z).bPressed) {
			chip8.key[0xA] = 1; std::cout << "Z" << std::endl;
		}
		else if (GetKey(olc::Key::X).bPressed) {
			chip8.key[0x0] = 1; std::cout << "X" << std::endl;
		}
		else if (GetKey(olc::Key::C).bPressed) {
			chip8.key[0xB] = 1; std::cout << "C" << std::endl;
		}
		else if (GetKey(olc::Key::V).bPressed) {
			chip8.key[0xF] = 1; std::cout << "V" << std::endl;
		}


		// If the draw flag is set, update the screen
		if (chip8.draw)
		{
			for (int j = 0; j < 32; j++)
				for (int i = 0; i < 64; i++)
				{
					if (chip8.display[(j * 64) + i] == 0)
						Draw(i, j, olc::BLACK);
					else
						Draw(i, j, olc::RED);
				}
			chip8.draw = false; // The screen has been updated, so we can disable the flag
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Sleep thread for 16ms (limit to ~60fps)
		return true;
	}
private:
	cpu chip8 = cpu();
};




int main()
{
	Emulator main;
	if (main.Construct(64, 32, 10, 10))
		main.Start();

	return 0;
}
