#include "ui.h"

namespace calc {
    Element UI::render_input() {
        return hbox(text(" Expression: "), expression_input_box->Render());
    }

    Element UI::render_output() {
        std::string result = "Your expression: ";
        result.append(logic_ref.expression);
        std::string result2 = "Result: ";
        result2.append(logic_ref.process_math());
        return vbox({text(result), separator(), text(result2)});
    }

    bool UI::process_events(Event event) {
        if (event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        }
        else if (event == Event::Return) {
            element_output = render_output();
            logic_ref.expression.clear();
            return true;
        }
        return false;
    }

    void UI::start() {
        auto component = Container::Vertical({ expression_input_box });
        auto renderer = Renderer(component, [&]
            { return vbox({ render_input(), separator(), element_output }) | border; });
        renderer |= CatchEvent([&](Event event)
            { return process_events(event); });
        screen.Loop(renderer);
    }

}