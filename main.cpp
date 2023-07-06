#include"Logic.h"
//#define getline cin.ignore(); getline

void Start();
void End();

int main()
{
	Start();

	cout << "=================================== I love Nemo =========================\n";
	string ans;
	Person per;

	while (true)
	{
		cout << "\n1-Log in\n2-Register\n3-Exit\n--> ";
		getline(cin, ans);
		if (ans == "1")
		{
			per.log_in();
			if (theUser == doctor) {
				Doctor doc;
			}
			else if (theUser == patient) {
				Patient pat;
			}
		}
		else if (ans == "2")
		{
			per.Register();
			if (theUser == doctor) {
				Doctor doc;
			}
			else if (theUser == patient) {
				Patient pat;
			}
		}
		else if (ans == "3")
		{
			break;
		}
		else
		{
			cout << "\aInvalid choice.. please try again";
		}
	}

	End();
	return 0;
}

void Start()
{
}

void End()
{
}