package li3;

import common.MyLog;
import common.Pair;
import engine.TCD;

import java.time.LocalDate;
import java.time.Month;
import java.util.List;

class Main {


    public static void main(String[] args){

        /*
            LOG CONFIGURATION
        */
        MyLog log = new MyLog("results");
        MyLog logtime = new MyLog("times");
        /* -------------------------------------------------------------------------------------------*/

        long before, after;
        TADCommunity qe = new TCD();

        /*
            LOAD PHASE
         */
        try {
            before = System.currentTimeMillis();
            qe.load(args[0]);
            after = System.currentTimeMillis();
            logtime.writeLog("LOAD -> "+(after-before)+" ms");
        } catch(IndexOutOfBoundsException e){
            System.out.println("Deve passar o caminho do dump como argumento.");
        }


        /*
           Query 1
        */

        before = System.currentTimeMillis();
        Pair<String,String> q1 = qe.infoFromPost(796430);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 1: -> "+(after-before)+" ms");
        log.writeLog("Query 1 -> " + q1);

        /*
           Query 2
        */
        before = System.currentTimeMillis();
        List<Long> q2 = qe.topMostActive(10);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 2 -> "+(after-before)+" ms");
        log.writeLog("Query 2 -> "+q2);

        /*
           Query 3
        */

        before = System.currentTimeMillis();
        Pair<Long,Long> q3 = qe.totalPosts(LocalDate.of(2014, Month.JANUARY,1),
        LocalDate.of(2014,Month.DECEMBER,31));
        after = System.currentTimeMillis();
        logtime.writeLog("Query 3 -> "+(after-before)+" ms");
        log.writeLog("Query 3 -> "+q3);

        /*
           Query 4
        */

        before = System.currentTimeMillis();
        List<Long> query4 = qe.questionsWithTag("nautilus", LocalDate.of(2014, Month.JANUARY, 1),
                LocalDate.of(2014, Month.JANUARY,31));
        after = System.currentTimeMillis();
        logtime.writeLog("Query 4 -> " + (after - before) + " ms");
        log.writeLog("Query 4 -> " + query4);

        /*
           Query 5
        */
        before = System.currentTimeMillis();
        Pair<String, List<Long>> q5 = qe.getUserInfo(15811);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 5 -> "+(after-before)+" ms");
        log.writeLog("Query 5 -> "+q5);

        /*
           Query 6
        */

        before = System.currentTimeMillis();
        List<Long> q6 = qe.mostVotedAnswers(50, LocalDate.of(2013, Month.MAY, 1),
                LocalDate.of(2013, Month.MAY,6));
        after = System.currentTimeMillis();
        logtime.writeLog("Query 6 -> " + (after - before) + " ms");
        log.writeLog("Query 6 -> " + q6);

        /*
           Query 7
        */
        before = System.currentTimeMillis();
        List<Long> q7 = qe.mostAnsweredQuestions(10, LocalDate.of(2014,Month.AUGUST,1),
                LocalDate.of(2014,Month.AUGUST,10));
        after = System.currentTimeMillis();
        logtime.writeLog("Query 7 -> "+(after-before)+" ms");
        log.writeLog("Query 7 -> "+q7);

        /*
           Query 8
        */

        before = System.currentTimeMillis();
        List<Long> q8 = qe.containsWord(10, "glib");
        after = System.currentTimeMillis();
        logtime.writeLog("Query 8 -> " + (after - before) + " ms");
        log.writeLog("Query 8 -> " + q8);

        /*
           Query 9
        */
        before = System.currentTimeMillis();
        List<Long> q9 = qe.bothParticipated(5, 253, 455);
        after = System.currentTimeMillis();
        logtime.writeLog("Query9 -> " + (after - before) + " ms");
        log.writeLog("Query 9 -> " + q9);

        /*
           Query 10
        */
        before = System.currentTimeMillis();
        long q10 = qe.betterAnswer(30334);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 10 -> "+(after-before)+" ms");
        log.writeLog("Query 10 -> "+q10);

        /*
            Query 11
        */
        before = System.currentTimeMillis();
        List<Long> q11 = qe.mostUsedBestRep(10, LocalDate.of(2014,Month.JANUARY, 1),
                LocalDate.of(2014,Month.DECEMBER,31));
        after = System.currentTimeMillis();
        logtime.writeLog("Query 11 -> "+(after-before)+" ms");
        log.writeLog("Query 11 -> "+q11);

        /*
            CLEAN PHASE
         */
        before = System.currentTimeMillis();
        qe.clear();
        after = System.currentTimeMillis();
        logtime.writeLog("CLEAN -> "+(after-before)+" ms");
    }

}


