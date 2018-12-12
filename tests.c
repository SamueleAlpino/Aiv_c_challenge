#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION

#include "aiv_unit_test.h"
#include "clock.h"
#include "context.h"

TEST(clock_move)
{
    context_t ctx ;
    new_context(&ctx, 1024,768,"Test");

    time_t theTime;
    struct tm *aTime;
    int seconds = 0;
    theTime = time(NULL);
    aTime = localtime(&theTime);
    seconds = aTime->tm_sec;

    analogic_clock_t *my_clock = init_clock("hand.png", ctx.width / 2, ctx.height / 2, 0, ctx.renderer);

    move_clock(ctx.renderer, my_clock, seconds);

    if(seconds == 0)
    {
       ASSERT_THAT( my_clock->angle = 0);
    }
   
    ASSERT_THAT( my_clock->angle != 0);
    
}

TEST(clock_init)
{
    context_t ctx ;
    new_context(&ctx, 1024,768,"Test");

    analogic_clock_t *my_clock = init_clock("hand.png", ctx.width / 2, ctx.height / 2, 0, ctx.renderer);
 
    ASSERT_THAT( my_clock != NULL );
}

TEST(clock_move_next_frame)
{
    context_t ctx ;
    new_context(&ctx, 1024,768,"Test");

    time_t theTime;
    struct tm *aTime;
    int seconds = 0;
    theTime = time(NULL);
    aTime = localtime(&theTime);
    seconds = aTime->tm_sec;

    analogic_clock_t *my_clock = init_clock("hand.png", ctx.width / 2, ctx.height / 2, 0, ctx.renderer);

    move_clock(ctx.renderer, my_clock, seconds);

    int angle = my_clock->angle;

    move_clock(ctx.renderer, my_clock, seconds);

    int next_angle = my_clock->angle;

    ASSERT_THAT(next_angle = angle + 6);
    
}

int main(int argc, char**argv)
{
    RUN_TEST(clock_init);
    RUN_TEST(clock_move);
    RUN_TEST(clock_move_next_frame);

    
    PRINT_TEST_RESULTS();
    return 0; 
}