int ball_counter_pin = 3; // define the obstacle avoidance sensor interface
int val;// define numeric variables val

int NUM_BALLS_COLLECTED = 0;

bool is_ball_passing = true;

void setup ()
{
  Serial.begin(9600);
  pinMode (ball_counter_pin, INPUT);
}
void loop ()
{
  count_balls();
}


void count_balls()
{
  val = digitalRead (ball_counter_pin);
  if (val == HIGH)
  {
    if (!is_ball_passing){
      is_ball_passing = true;
      NUM_BALLS_COLLECTED ++;
      Serial.print("Num balls collected so far:");
      Serial.println(NUM_BALLS_COLLECTED);
      delay(50);
    }
  }
  else
  {
    delay(50);
    is_ball_passing = false;
  }
}
