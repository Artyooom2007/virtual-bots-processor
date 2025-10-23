// I WANNA BOTS!
// I can't count how much days I doing this BOTS.         (18 days)
// But I will put this in unit and compile to .dll or .so
// Or I just will rewrite this to .c or .js , because Pascal ((sucks)) is not so multiplatform.

program mahbots;

uses crt, sysUtils, math, graph, myownbots;


//const //=================CONSTS=====================

var //===================VARS========================

      stop: boolean;                                        // IT'S TIME TO STOP

      gd,gm,error: integer;                                 // You don't need this, right?


//=====================PROCEDURES====================


procedure botsGenStatus;         // 1 - Attacker  2 - Bait  3 - Defender  4 - Sentry
var a,b: integer;

begin
        randomize;

        for a:= 1 to MAX_BOTS_GROUPS do
                for b:= 1 to MAX_BOTS do
                        begin
                                bots[a,1].status := 4;
                                bots[a,b].status := random(2)+1;


                        end;

end;


procedure botsGenPlan;           // 0- nothing 1- walk  2- shoot 3- wait
                                 // 0 - really, this does nothing!
                                 // 1[2,3] - XY
                                 // 2[2,3] - bot ID, how much shoot (X times)
                                 // 3[2] - time
var    a,b : integer;
       closestEnemy1, closestEnemy2, closestDefence, rndNumber1, rndNumber2: integer;
       antipodd: integer;
begin
        randomize;
        for a := 1 to MAX_BOTS_GROUPS  do
        begin
                antipodd := antipod(a);
                for b:= 1 to MAX_BOTS do
                begin
                        if bots[a,b].planReached = true then
                        begin
                                        // There it starts. Actually, after this "if" goes madness.

                                        if bots[a,b].status = 1 then
                                        begin
                                                        closestEnemy1 := nearestEnemy(bots[a,b].x,bots[a,b].y,antipodd);
                                                        rndNumber1 := random(20)+3;
                                                        rndNumber2 := random(20)+3;

                                                        if closestEnemy1 <= 0 then continue;

                                                        bots[a,b].plan[1,1] := 1;       //=====1======================

                                                        if (bots[antipodd,closestEnemy1].x) > (bots[a,b].x) then

                                                             begin bots[a,b].plan[1,2] := bots[a,b].x - rndNumber1;
                                                             closestEnemy2 := nearestEnemy(bots[a,b].x - rndNumber1, bots[a,b].y, antipodd);
                                                             closestDefence := nearestDefence(bots[a,b].x - rndNumber1, bots[a,b].y); end

                                                        else begin bots[a,b].plan[1,2] := bots[a,b].x + rndNumber1;
                                                             closestEnemy2 := nearestEnemy(bots[a,b].x + rndNumber1, bots[a,b].y, antipodd);
                                                             closestDefence := nearestDefence(bots[a,b].x + rndNumber1, bots[a,b].y); end;

                                                        if (bots[antipodd,closestEnemy1].y) > (bots[a,b].y) then

                                                             begin bots[a,b].plan[1,3] := bots[a,b].y - rndNumber2;
                                                             closestEnemy2 := nearestEnemy(bots[a,b].x, bots[a,b].y - rndNumber2, antipodd);
                                                             closestDefence := nearestDefence(bots[a,b].x, bots[a,b].y - rndNumber2); end

                                                        else begin bots[a,b].plan[1,3] := bots[a,b].y + rndNumber2;
                                                             closestEnemy2 := nearestEnemy(bots[a,b].x, bots[a,b].y + rndNumber2, antipodd);
                                                             closestDefence := nearestDefence(bots[a,b].x, bots[a,b].y + rndNumber2); end;

                                                        if closestEnemy2 <= 0 then closestEnemy2 := closestEnemy1;

                                                        bots[a,b].plan[2,1] := 2;       //======2=====================
                                                        bots[a,b].plan[2,2] := closestEnemy2;
                                                        bots[a,b].plan[2,3] := random(2)+1;

                                                        bots[a,b].plan[3,1] := 1;       //======3======================

                                                        bots[a,b].plan[3,2] := defences[closestDefence].x;
                                                        bots[a,b].plan[3,3] := defences[closestDefence].y;

                                                        bots[a,b].plan[4,1] := 3;       //======4======================
                                                        bots[a,b].plan[4,2] := random(20)+10;

                                        end

                                        else if bots[a,b].status = 2 then
                                        begin

                                                        rndNumber1 := random(10) + 10;
                                                        rndNumber2 := random(10) + 10;

                                                        closestEnemy1 := nearestEnemy(bots[a,b].x, bots[a,b].y, antipodd);

                                                        if closestEnemy1 <= 0 then continue;

                                                        bots[a,b].plan[1,1] := 1;       //=======1=======================

                                                        if bots[antipodd,closestEnemy1].x > bots[a,b].x then
                                                        bots[a,b].plan[1,2] := bots[antipodd,closestEnemy1].x + rndNumber1
                                                        else
                                                        bots[a,b].plan[1,2] := bots[antipodd,closestEnemy1].x - rndNumber1;

                                                        if bots[antipodd,closestEnemy1].y > bots[a,b].y then
                                                        bots[a,b].plan[1,3] := bots[antipodd,closestEnemy1].y + rndNumber2
                                                        else
                                                        bots[a,b].plan[1,3] := bots[antipodd,closestEnemy1].y - rndNumber2;

                                                        bots[a,b].plan[2,1] := 1;       //=======2========================

                                                        closestEnemy2:= nearestEnemy(bots[a,b].plan[1,2], bots[a,b].plan[1,3], antipodd);

                                                        if bots[antipodd,closestEnemy2].x > bots[a,b].x then
                                                        bots[a,b].plan[2,2] := bots[antipodd,closestEnemy2].x + rndNumber1
                                                        else
                                                        bots[a,b].plan[2,2] := bots[antipodd,closestEnemy2].x - rndNumber1;

                                                        if bots[antipodd,closestEnemy1].y > bots[a,b].y then
                                                        bots[a,b].plan[2,3] := bots[antipodd,closestEnemy2].y + rndNumber2
                                                        else
                                                        bots[a,b].plan[2,3] := bots[antipodd,closestEnemy2].y - rndNumber2;

                                                        bots[a,b].plan[3,1] := 1;       //=======3========================

                                                        closestDefence := nearestDefence(bots[a,b].plan[2,2], bots[a,b].plan[2,3]);

                                                        bots[a,b].plan[3,2] := defences[closestDefence].x;
                                                        bots[a,b].plan[3,3] := defences[closestDefence].y;

                                                        bots[a,b].plan[4,1] := 0;       //=======4========================

                                        end

                                        else if bots[a,b].status = 3 then
                                        begin
                                                        rndNumber1 := random(3)+1;

                                                        closestEnemy1 := nearestEnemy(bots[a,b].x, bots[a,b].y, antipodd);

                                                        if closestEnemy1 <= 0 then continue;

                                                        bots[a,b].plan[1,1] := 1;       //=======1=========================

                                                             if rndNumber1 = 1 then bots[a,b].plan[1,2] := bots[a,b].x - 2
                                                        else if rndNumber1 = 2 then bots[a,b].plan[1,2] := bots[a,b].x + 2
                                                        else if rndNumber1 = 3 then bots[a,b].plan[1,3] := bots[a,b].y - 2
                                                        else if rndNumber1 = 4 then bots[a,b].plan[1,3] := bots[a,b].y + 2;

                                                        bots[a,b].plan[2,1] := 2;       //=======2=========================


                                                        bots[a,b].plan[2,2] := closestEnemy1;
                                                        bots[a,b].plan[2,3] := 1;

                                                        bots[a,b].plan[3,1] := 1;       //=======3=========================

                                                        closestDefence := nearestDefence(bots[a,b].x,bots[a,b].y);

                                                        bots[a,b].plan[3,2] := defences[closestDefence].x;
                                                        bots[a,b].plan[3,3] := defences[closestDefence].y;

                                                        bots[a,b].plan[4,1] := 3;       //=======4==========================
                                                        bots[a,b].plan[4,2] := random(20);
                                        end

                                        else if bots[a,b].status = 4 then
                                        begin
                                                        closestEnemy1 := nearestEnemy(bots[a,b].x, bots[a,b].y, antipodd);

                                                        if closestEnemy1 <= 0 then continue;

                                                        bots[a,b].plan[1,1] := 2;       //=======1==========================

                                                        bots[a,b].plan[1,2] := closestEnemy1;
                                                        bots[a,b].plan[1,3] := random(2)+1;

                                                        bots[a,b].plan[2,1] := 3;       // 2
                                                        bots[a,b].plan[2,2] := 3;

                                                        bots[a,b].plan[3,1] := 0;       // 3        DUMB ASS
                                                        bots[a,b].plan[4,1] := 0;       // 4

                                                        writeln(closestEnemy1);
                                        end;

                                        bots[a,b].planReached := false;
                                        bots[a,b].action := 1;

                        end;
                end;
        end;
end;

procedure planExecution;

var a,b,c: integer;

begin
        for a:= 1 to MAX_BOTS_GROUPS do
        begin
                for b:= 1 to MAX_BOTS do
                begin

                 if bots[a,b].planReached = false then
                 begin
                        c := bots[a,b].action;
                        if (c < 1) or (c > 4) then
                        begin
                                bots[a,b].action := 1;
                                c := 1;
                        end;

                        if bots[a,b].plan[c,1] = 0 then
                        begin
                                bots[a,b].action := bots[a,b].action + 1;
                        end

                        else if bots[a,b].plan[c,1] = 1 then
                        begin
                                botMove(a, b, bots[a,b].plan[ c ,2], bots[a,b].plan[c,3]);

                                if (bots[a,b].x = bots[a,b].plan[c,2]) and (bots[a,b].y = bots[a,b].plan[c,3]) then
                                bots[a,b].action := bots[a,b].action + 1;

                            //  writeln(bots[a,b].action, ' ', a, ' ', b);
                        end

                        else if bots[a,b].plan[c,1] = 2 then
                        begin

                                if bots[a,b].plan[c,3] > 0 then
                                begin
                                        botShoot(a, b, bots[antipod(a), (bots[a,b].plan[c,2])].x, bots[antipod(a),(bots[a,b].plan[c,2])].y);
                                        bots[a,b].plan[c,3] := bots[a,b].plan[c,3] - 1;

                                end;
                                bots[a,b].action := bots[a,b].action + 1;
                        end

                        else if bots[a,b].plan[c,1] = 3 then
                        begin
                                if bots[a,b].plan[c,2] > 0 then
                                begin
                                        bots[a,b].plan[c,2] := bots[a,b].plan[c,2] - 1;

                                end
                               else bots[a,b].action := bots[a,b].action + 1;

                        end;

                        if bots[a,b].action > 4 then bots[a,b].planReached := true;

                  end
                  else continue;
                end;
        end;
end;

procedure drawAll;
var a, b, c: integer;
begin





        for a := 1 to MAX_BOTS_GROUPS do
        begin

                 for c:= 1 to MAX_PROJECTILES do
                 begin
                        if projectiles[a,c].exist = true then
                        begin


                                setFillstyle(SolidFill, 0);
                                Bar((150+ projectiles[a,c].x * 5) - 10, (150+ projectiles[a,c].y * 5) - 10, (150+ projectiles[a,c].x * 5) + 10, (150+ projectiles[a,c].y * 5) + 10);

                                setFillStyle(SolidFill, 5 + a);
                                Bar((150+ projectiles[a,c].x * 5) + 2, (150+ projectiles[a,c].y * 5) + 2, (150+ projectiles[a,c].x * 5) + 4, (150+ projectiles[a,c].y * 5) + 4);
                        end
                        else continue;
                 end;

                 for b := 1 to MAX_BOTS do
                 begin
                        if bots[a,b].live = true then
                        begin
                                setFillstyle(SolidFill, 0);
                                Bar((150+ bots[a,b].x * 5)-10, (150+ bots[a,b].y * 5)-10, (150+ bots[a,b].x * 5) + 10, (150+ bots[a,b].y * 5) + 20);

                                setFillStyle(SolidFill, 3 + a);
                                Bar(150+ bots[a,b].x * 5, 150+ (bots[a,b].y * 5), (150+ bots[a,b].x * 5) + 5, (150+ bots[a,b].y * 5) + 5);

                                end
                        else continue;
                 end;


        end;


        for c := 1 to MAX_DEFENCE_POINTS do
        begin
                setFillStyle(SolidFill, 8);
                Bar(150+ defences[c].x * 5, 150+ defences[c].y * 5, (150+ defences[c].x * 5) + 5, (150+ defences[c].y * 5) + 5);
        end;


end;

//====================MAIN=SCRIPT====================
BEGIN
        initGraph(gd,gm,'');

        stop := false;

        AllInit;

        delay(50);

        botsGenStatus;
        botsGenPlan;

        while stop = false do  // DON'T STOP PLEASE JUST DON'T STOP JUST DON'T STOP
        begin

                botsGenPlan;
                planExecution;
                projectilesCalculate;
                drawAll;



       // delay(10);
       // readln;


        end;


END.

