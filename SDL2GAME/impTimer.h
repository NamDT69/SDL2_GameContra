#ifndef TIMER_
#define TIMER_

class ImpTimer{
public:
	ImpTimer();
	~ImpTimer();
	void start();
	void stop();
	void paused();
	void unPaused();
	
	int getTicks();

	bool is_Started();
	bool is_Paused();

private:
	int start_tick_; // thoi diem no chay 
	int paused_tick_; // tam dung
	bool is_paused_;
	bool is_started_;
};

#endif