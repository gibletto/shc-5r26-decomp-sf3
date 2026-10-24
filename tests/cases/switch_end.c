/* Nested switch exits and a control with code between the two ends. */
struct state { int outer, middle, inner, value; };
extern void update(struct state *s);

void nested_end(struct state *s)
{
    switch (s->outer) {
    case 0:
        switch (s->middle) {
        case 0:
            update(s);
            break;
        case 1:
            switch (s->inner) {
            case 0:
                if (s->value == 0) s->inner++;
                else s->value--;
                break;
            case 1:
                if (s->value < 10) {
                    update(s);
                    s->inner--;
                }
            }
#if WITH_CODE
            update(s);
#endif
        }
        break;
    default:
        update(s);
        break;
    }
}
