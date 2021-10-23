#ifndef DRIVE_BASE
#define DRIVE_BASE

class DriveBase {
public:
  void test();

protected:
  void test2();
  double maxSpeed = 128;
  double midSpeed = 69;
  double minSpeed = 10;
  double speedBias = 1;

private:
  void test3();
};

#endif