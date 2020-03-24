package li3;

import java.time.LocalDate;
import java.util.List;
import common.Pair;

public interface TADCommunity {
    void load(String dumpPath);

    // Query 1
    Pair<String,String> infoFromPost(long id);

    // Query 2
    List<Long> topMostActive(int N);

    // Query 3
    Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end);

    // Query 4
    List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end);

    // Query 5
    Pair<String, List<Long>> getUserInfo(long id);

    // Query 6
    List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end);

    // Query 7
    List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end);

    // Query 8
    List<Long> containsWord(int N, String word);

    // Query 9
    List<Long> bothParticipated(int N, long id1, long id2);

    // Query 10
    long betterAnswer(long id);

    // Query 11
    List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end);

    void clear();
}



