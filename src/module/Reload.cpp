#include"Reload.h"
Attribute& operator+=(Attribute& Body, const Attribute& Effection)
{
	Body.MaxBlood += Effection.MaxBlood;
	Body.MaxEnergy += Effection.MaxEnergy;
	Body.Ma += Effection.Ma;
	Body.Md += Effection.Md;
	Body.Pa += Effection.Pa;
	Body.Pd += Effection.Pd;
	Body.Speed += Effection.Speed;
	Body.Blood = ((Body.Blood + Effection.Blood) > Body.MaxBlood) ? Body.MaxBlood : Body.Blood + Effection.Blood;
	Body.Energy = ((Body.Energy + Effection.Energy) > Body.MaxEnergy) ? Body.MaxEnergy : Body.Energy + Effection.Energy;
	Body.Frequence += Effection.Frequence;
	Body.CrRate += Effection.CrRate;
	return Body;
}
Attribute& operator-=(Attribute& Body, const Attribute& Effection)
{
	Body.MaxBlood -= Effection.MaxBlood;
	Body.MaxEnergy -= Effection.MaxEnergy;
	Body.Ma = ((Body.Ma - Effection.Ma) >= 0) ? Body.Ma - Effection.Ma : 0;
	Body.Md = ((Body.Md - Effection.Md) >= 0) ? Body.Md - Effection.Md : 0;
	Body.Pa = ((Body.Pa - Effection.Pa) >= 0) ? Body.Pa - Effection.Pa : 0;
	Body.Pd = ((Body.Pd - Effection.Pd) >= 0) ? Body.Pd - Effection.Pd : 0;
	Body.Speed = ((Body.Speed - Effection.Speed) >= 0) ? Body.Speed - Effection.Speed : 0;
	Body.Frequence = ((Body.Frequence - Effection.Frequence) >= 0) ? Body.Frequence - Effection.Frequence : 0.2;//攻速最低不能为零 否则会除法溢出
	Body.CrRate = ((Body.CrRate - Effection.CrRate) >= 0) ? Body.CrRate - Effection.CrRate : 0;
	return Body;
}
Attribute operator+(const Attribute& Effection1, const Attribute& Effection2)
{
	//似乎一般+号只会用于效果叠加 那么就没有最大生命值这么一说了  所以这一项也就不用管了
	Attribute Tmp;
	//Tmp.MaxBlood=Effection1.MaxBlood + Effection2.MaxBlood;
	//Effection1.MaxEnergy + Effection2.MaxEnergy;
	Tmp.Ma = Effection1.Ma + Effection2.Ma;
	Tmp.Md = Effection1.Md + Effection2.Md;
	Tmp.Pa = Effection1.Pa + Effection2.Pa;
	Tmp.Pd = Effection1.Pd + Effection2.Pd;
	Tmp.Speed = Effection1.Speed + Effection2.Speed;
	Tmp.Blood = Effection1.Blood + Effection2.Blood;
	Tmp.Energy = Effection1.Energy + Effection2.Energy;
	Tmp.Frequence = Effection1.Frequence + Effection2.Frequence;
	Tmp.CrRate = Effection1.CrRate + Effection2.CrRate;

	return Tmp;
}
Special& operator-=(Special& Body, const Special& Effection)
{
	Body.PhysicalPercent = ((Body.PhysicalPercent - Effection.PhysicalPercent) > 0) ? Body.PhysicalPercent - Effection.PhysicalPercent : 0;
	Body.MagicPercent = ((Body.MagicPercent - Effection.MagicPercent) > 0) ? Body.MagicPercent - Effection.MagicPercent : 0;
	Body.SuckBlood = ((Body.SuckBlood - Effection.SuckBlood) > 0) ? Body.SuckBlood - Effection.SuckBlood : 0;
	Body.SuckMagic = ((Body.SuckMagic - Effection.SuckMagic) > 0) ? Body.SuckMagic - Effection.SuckMagic : 0;
	return Body;
}
Special& operator+=(Special& Body, const Special& Effection)
{
	Body.PhysicalPercent += Effection.PhysicalPercent;
	Body.MagicPercent += Effection.MagicPercent;
	Body.SuckBlood += Effection.SuckBlood;
	Body.SuckMagic += Effection.SuckMagic;
	return Body;
}
Buff& operator+=(Buff& Body, const Buff& Adder)
{
	Body.TimeLeft += Adder.TimeLeft;
	Body.Effection += Adder.Effection;
	Body.special += Adder.special;
	return Body;
}
bool operator!=(const COORD& cd1, const COORD& cd2)
{
	return (cd1.X != cd2.X) || (cd1.Y != cd2.Y);
}
bool operator==(const COORD& cd1, const COORD& cd2)
{
	return (cd1.X == cd2.X) && (cd1.Y == cd2.Y);
}
