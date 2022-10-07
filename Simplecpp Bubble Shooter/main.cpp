#include <simplecpp>
#include "shooter.h"
#include "bubble.h"
#include "canvas.h"

/* Simulation Vars */
double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 500;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);
int score=0;


void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}

vector<Bubble> create_bubbles(int level)
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    for(int i=1;i<=1+level;i++)
    {
        double spawn_x=1.0*i*WINDOW_X/(2+level);
        double spawn_y=75.0+(92*i)%75;
        double radius=BUBBLE_DEFAULT_RADIUS;//*pow(1.25,level-1);
        double vx=pow(-1,i-1)*pow(1.25,level-1)*((73*i)%100+50);
        double vy=pow(1.25,level-1)*pow(-1,i/2)*((43*i)%100);
        double ay=BUBBLE_DEFAULT_AY*pow(1.5,level-1);
        bubbles.push_back(Bubble(spawn_x, spawn_y, radius, vx, vy, ay, COLOR((69*level)%150+50,(42*level)%150+50,(93*level)%150+50)));
    }

    //bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, BUBBLE_DEFAULT_AY, COLOR(255,105,180)));
    return bubbles;
}

bool Collision(double r1,double x1,double y1,double r2,double x2,double y2)
{
    double d=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    return d<r1+r2;
}

Rectangle health_bar(int health)
{
    Rectangle R1;
    if(health==5)
    {
        R1=Rectangle(600,25,100,25);
        R1.setColor(COLOR(0,255,0));
        R1.setFill(true);
    }
    else if(health==4)
    {
        R1=Rectangle(590,25,80,25);
        R1.setColor(COLOR(127,255,0));
        R1.setFill(true);
    }
    else if(health==3)
    {
        R1=Rectangle(580,25,60,25);
        R1.setColor(COLOR(255,255,0));
        R1.setFill(true);
    }
    else if(health==2)
    {
        R1=Rectangle(570,25,40,25);
        R1.setColor(COLOR(255,127,0));
        R1.setFill(true);
    }
    else if(health==1)
    {
        R1=Rectangle(560,25,20,25);
        R1.setColor(COLOR(255,0,0));
        R1.setFill(true);
    }
    return R1;
}

Text Mins(int timer)
{
    Text mins=Text(850,25,timer/6000);
    if(timer<=1000&&timer%50==0&&timer%100==0)
        mins.setColor(COLOR(255,0,0));
    else if(timer<=1000&&timer%50==0&&timer%100!=0)
        mins.setColor(COLOR(0,0,0));
    return mins;
}

Text Secs(int timer)
{
    int s=(timer%6000)/100;
    Text secs;

    switch(s)
    {
        case 9:
        secs=Text(880,25,"09");
        break;
        case 8:
        secs=Text(880,25,"08");
        break;
        case 7:
        secs=Text(880,25,"07");
        break;
        case 6:
        secs=Text(880,25,"06");
        break;
        case 5:
        secs=Text(880,25,"05");
        break;
        case 4:
        secs=Text(880,25,"04");
        break;
        case 3:
        secs=Text(880,25,"03");
        break;
        case 2:
        secs=Text(880,25,"02");
        break;
        case 1:
        secs=Text(880,25,"01");
        break;
        case 0:
        secs=Text(880,25,"00");
        break;
        default:
        secs=Text(880,25,s);
        break;
    }

    if(timer<=1000&&timer%50==0&&timer%100==0)
        secs.setColor(COLOR(255,0,0));
    else if(timer<=1000&&timer%50==0&&timer%100!=0)
        secs.setColor(COLOR(0,0,0));

    return secs;
}

int main()
{
    initCanvas("Bubble Trouble", 960, 540);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    Line b2(0, 50, WINDOW_X, 50);
    b2.setColor(COLOR(0, 0, 255));

    Line b3(1, 50, 1, 500);
    b3.setColor(COLOR(0, 0, 255));

    Line b4(959, 50, 959,500);
    b4.setColor(COLOR(0, 0, 255));

    Text SCORE=Text(50,25,"SCORE - ");
    SCORE.setColor(COLOR(0,0,255));

    Text HEALTH=Text(500,25,"HEALTH ");
    HEALTH.setColor(COLOR(0,0,255));

    Text INVINCIBILITY=Text(480,270,"INVINCIBILITY");
    INVINCIBILITY.setColor(COLOR(255,255,255));

    Text sc=Text(100,25,score);
    sc.setColor(COLOR(0,0,0));

    Text LEVEL=Text(275,25,"LEVEL ");
    LEVEL.setColor(COLOR(0,0,255));

    Text TIMER=Text(800,25,"TIME - ");
    TIMER.setColor(COLOR(0,0,255));

    Text colon=Text(865,25,":");
    Text mins,secs;

    int level=1;
    int health=5;
    int timer;

    Text lvl=Text(325,25,level);
    lvl.setColor(COLOR(0,0,0));

    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    while(true)
    {
        // Intialize the shooter
        Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

        // Initialize the bubbles
        vector<Bubble> bubbles = create_bubbles(level);

        // Initialize the bullets (empty)
        vector<Bullet> bullets;

        XEvent event;

        bool collision_bubble;

        health=5;

        bool invincibility=false;
        long invincibility_time=50;

        bool cooldown=false;
        long cooldown_time=25;

        Rectangle r=health_bar(health);

        Rectangle R=Rectangle(600,25,100,25);
        R.setColor(COLOR(0,0,0));

        timer=500*(1+level)+98;

        mins=Mins(timer);
        secs=Secs(timer);

        // Main game loop
        while (timer!=0)
        {
            //Check input
            bool pendingEvent = checkEvent(event);
            if (pendingEvent)
            {
                // Get the key pressed
                char c = charFromEvent(event);
                msg_cmd[msg_cmd.length() - 1] = c;
                charPressed.setMessage(msg_cmd);

                // Update the shooter
                if(c == 'a')
                    shooter.move(STEP_TIME, true);
                else if(c == 'd')
                    shooter.move(STEP_TIME, false);
                else if(c == 'w'&&!cooldown)
                {
                    bullets.push_back(shooter.shoot(level));
                    cooldown=true;
                    cooldown_time=0;
                    if(score>0)
                    {
                        score--;
                        sc=Text(100,25,score);
                    }
                }
                else if(c == 'q')
                    return 0;
                else if(c == 'r')
                    continue;
            }

            //cooldown of 0.25s
            cooldown_time++;
            if(cooldown_time>=10)
                cooldown=false;

            // Update the bubbles
            move_bubbles(bubbles);

            // Update the bullets
            move_bullets(bullets);

            //check bullet collisions
            size_t i,j;
            bool collision_bullet=false;

            for(i=0;i<bullets.size();i++)
            {
                for(j=0;j<bubbles.size();j++)
                {
                    if(Collision(bullets[i].get_width()/2,bullets[i].get_center_x(),bullets[i].get_center_y(),bubbles[j].get_radius(),bubbles[j].get_center_x(),bubbles[j].get_center_y()))
                    {
                        collision_bullet=true;
                        break;
                    }
                }
                if(collision_bullet)
                {
                    break;
                }
            }

            if(collision_bullet)
            {
                bubbles.erase(bubbles.begin()+j);
                bullets.erase(bullets.begin()+i);
                score=score+level;
                sc=Text(100,25,score);
                sc.setColor(COLOR(0,0,0));
            }

            //if all bubbles popped, level complete
            if(bubbles.size()==(size_t)0)
            {
                break;
            }

            //check bubble collison with shooter
            size_t k;

            collision_bubble=false;

            if(!invincibility)
            {
                for(k=0;k<bubbles.size();k++)
                {
                    double r1=bubbles[k].get_radius();
                    double x1=bubbles[k].get_center_x();
                    double y1=bubbles[k].get_center_y();

                    double r2=shooter.get_head_radius();
                    double x2=shooter.get_head_center_x();
                    double y2=shooter.get_head_center_y();

                    bool c1=Collision(r1,x1,y1,r2,x2,y2);
                    bool c2=Collision(r1,x1,y1,r2,x2,y2+8);
                    bool c3=Collision(r1,x1,y1,r2,x2,y2+16);
                    bool c4=Collision(r1,x1,y1,r2,x2,y2+24);
                    bool c5=Collision(r1,x1,y1,r2,x2,y2+32);

                    collision_bubble=c1||c2||c3||c4||c5;

                    if(collision_bubble)
                        break;
                }
            }

            if(collision_bubble)
            {
                health--;
                r=health_bar(health);

                R=Rectangle(600,25,100,25);
                R.setColor(COLOR(0,0,0));

                if(score>0)
                    score--;
                sc=Text(100,25,score);

                //reset invincibiity time
                invincibility_time=0;
            }

            //remove invincibility after 0.5s
            if(invincibility_time==25)
            {
                invincibility=false;
                INVINCIBILITY.setColor(COLOR(255,255,255));
            }

            else if(invincibility_time==0)
            {
                invincibility=true;
                INVINCIBILITY.setColor(COLOR(0,255,0));
            }

            invincibility_time++;

            if(timer%50==0)
            {
                mins=Mins(timer);
                if(timer<=1000&&timer%50==0&&timer%100==0)
                    colon.setColor(COLOR(255,0,0));
                else if(timer<=1000&&timer%50==0&&timer%100!=0)
                    colon.setColor(COLOR(0,0,0));
                secs=Secs(timer);
            }

            timer-=2;

            if(health==0)
                break;

            if(timer==0)
                break;

            wait(STEP_TIME);
        }

        if(bubbles.size()==(size_t)0)
        {
            vector<Bullet> b;
            bullets=b;
            Text t=Text(480,270,"LEVEL COMPLETE!");
            t.setColor(COLOR(0,0,0));
            invincibility_time=25;
            INVINCIBILITY.setColor(COLOR(255,255,255));
            wait(3);

            level++;
            lvl=Text(325,25,level);
        }
        if(health==0)
        {
            break;
        }
        if(timer==0)
        {
            break;
        }
    }
    if(health==0)
    {
        INVINCIBILITY.setColor(COLOR(255,255,255));
        Rectangle x=Rectangle(600,25,100,25);
        x.setColor(COLOR(0,0,0));

        Text t=Text(480,280,"GAME OVER!");
        t.setColor(COLOR(0,0,0));
        wait(5);
        return 0;
    }

    if(timer==0)
    {
        INVINCIBILITY.setColor(COLOR(255,255,255));
        Rectangle x=Rectangle(600,25,100,25);
        x.setColor(COLOR(0,0,0));
        mins=Mins(0);
        secs=Secs(0);

        Text t=Text(480,280,"TIME UP!");
        t.setColor(COLOR(0,0,0));
        wait(2);

        t=Text(480,280,"GAME OVER!");
        wait(5);
        return 0;
    }
}
