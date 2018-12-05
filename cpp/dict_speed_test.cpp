
/*


void test_speed_naive(Dictionary*& d) {
    std::vector<int> list;
    for (int i = 0; i < 20000; i++) {
        list.push_back(i);
    }

    std::random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        d->insert(*it, 0);
    }

    std::random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        assert(d->contains(*it));
    }

    std::random_shuffle(list.begin(), list.end());
    for (auto it = list.begin(); it!=list.end(); it++) {
        d->remove(*it);
        assert(!(d->contains(*it)));
    }
}


void test_correctness() {
    Dictionary *z, *t, *s;

    printf("Zip trees\n");
    z = new ZipTree;
    test_correctness_dict(z);
    delete z;

    printf("\nTreaps\n");
    t = new Treap;
    test_correctness_dict(t);
    delete t;

    printf("\nSkip lists\n");
    s = new SkipList(16, 0.5);
    test_correctness_dict(s);
    delete s;

}

void test_speed() {
    uint64 tic, tac;
    Dictionary *z, *t, *s;

    printf("\nSpeed test");
    printf("\nZip trees\n");
    z = new ZipTree;
    tic = GetTimeMs64();
    test_speed_naive(z);
    tac = GetTimeMs64();
    printf("time: %d ms\n", int (tac-tic));
    delete z;

    printf("\nTreaps\n");
    t = new Treap;
    tic = GetTimeMs64();
    test_speed_naive(t);
    tac = GetTimeMs64();
    printf("time: %d ms\n", int (tac-tic));
    delete t;

    printf("\nSkip lists\n");
    s = new SkipList(16, 0.5);
    tic = GetTimeMs64();
    test_speed_naive(s);
    tac = GetTimeMs64();
    printf("time: %d ms\n", int (tac-tic));
    delete s;
}

*/
