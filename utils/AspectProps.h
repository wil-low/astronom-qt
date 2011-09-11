#ifndef ASPECTPROPS_H
#define ASPECTPROPS_H

class AspectProps
{
public:
	AspectProps();
	AspectProps(int id, double angle, double orb, int signDiff,
				char angleChar, char signChar);
	void set(double angle, double orb, int signDiff,
			 char angleChar, char signChar);

	int id() const;
	double angle() const;
	double orb() const;
	int signDiff() const;
	char angleChar() const;
	char signChar() const;

private:
	int id_;
	double angle_;
	double orb_;
	int signDiff_;
	char angleChar_;
	char signChar_;
};


#endif // ASPECTPROPS_H
