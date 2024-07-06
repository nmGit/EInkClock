#include "ClockScreen.h"
#include "Power.h"
#include "UI.h"

namespace Screens
{
	RealTimeClock::time_t time = {0};
	time_and_date_t time_and_date;
	bool set_time = false;

	void DoClockScreen(RealTimeClock &rtc)
	{
#ifdef NAM
		set_time = false;

		if (set_time)
		{

			rtc.SetDate(time);
		}

		rtc.GetDate(time);

		time_and_date.seconds = time.second;
		time_and_date.minutes = time.minute;
		time_and_date.hours = time.hour;
		// if (do_i_update(time_and_date))
		// {
		//
		// }
		draw_string(185, 58, "FRIDAY", BLACK, MEDIUM);
		draw_string(185, 82, "MARCH 29", BLACK, MEDIUM);
		if (time.hour > 12)
		{
			// draw_string(30, 75, "PM", BLACK, MEDIUM);
			time.hour -= 12;
		}
		else
		{
			// draw_string(30, 75, "A", BLACK, MEDIUM);
		}
		draw_time(158, 0, time.hour, time.minute);
		// refresh_display();

		refresh_display();

		Power::GoToSleep();
#endif // NAM
	}
}
 // namespace Screens