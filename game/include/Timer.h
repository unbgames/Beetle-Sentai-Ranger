#ifndef TIMER
#define TIMER

class Timer{
	public:
		Timer();
		~Timer();
		void Update(float dt);
		void Restart();
		float Get();

	private:
		float time;
};

#endif