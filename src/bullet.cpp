void Bullet::move(Direction d, float ElapsedTime,
		  std::vector<Object*> objects) {

  _x = this->getSprite().GetPosition().x;
  _y = this->getSprite().GetPosition().y;
  
  float velocity = speed * ElapsedTime;

  frame_buffer++;
  // std::cout << frame_buffer << ", " << frame << std::endl;
  if (frame_buffer%10 == 0) {
    frame++;
    //std::cout << frame_buffer << ", " << frame << std::endl;
    frame_buffer = 0;
  }

  if (frame == 3)
    frame = 0;      

  if (d == LEFT) {
    avatar.SetImage(left[frame]);
    facing = LEFT;
    _x += -velocity;
    if (_x > 0 and !collisionDetected(objects)) {
    avatar.Move(-velocity, 0);
    }
    else _x += velocity;
  }
  else if (d == RIGHT) {    
    avatar.SetImage(right[frame]);
    facing = RIGHT;
    _x += velocity;
    if (_x + width < SCREEN_WIDTH and !collisionDetected(objects)) {
    avatar.Move(velocity, 0);
    }
    else _x += -velocity;
  }
  else if (d == UP) {
    avatar.SetImage(up[frame]);
    facing = UP;
    _y += -velocity;
    if (_y > 0 and !collisionDetected(objects)) {
    avatar.Move(0, -velocity);    
    }
    else _y += velocity;
  }
  else if (d == DOWN) {
    avatar.SetImage(down[frame]);
    facing = DOWN;
    _y += velocity;
    if (_y + height < SCREEN_HEIGHT and !collisionDetected(objects)) {
    avatar.Move(0, velocity);
    }
    else _y += -velocity;
  }  
}
