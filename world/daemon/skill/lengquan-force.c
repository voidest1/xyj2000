// cracked by vikee 2/09/2002   vikee@263.net
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
        return
notify_fail("閸愰攱纭ョ粊鐐插閸欘亣鍏橀崥鎴濈瑎閻栬泛顒熼敍灞惧灗閺勵垯绮犳潻鎰暏(exert)娑擃厼顤冮崝鐘靛暃缂佸啫瀹抽妴淇搉");
}
string exert_function_file(string func)
{
        return CLASS_D("fighter") + "/lengquan-force/" + func;
}