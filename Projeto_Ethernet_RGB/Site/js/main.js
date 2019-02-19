var values = {};

$(document).ready(function () {
  ajustLastItem();
  loadPage("configFitaLedNathan", "Room Control");

  $(window).resize(function () {
    ajustLastItem();
  });

  $("#slide-out li").click(function () {
    let va = setInterval(ajustLastItem, 0);
    setTimeout(function () { clearInterval(va); }, 500);
  });

  $.each($.cookie(), function (i, val) {
    if (i.substring(0, 2) == "c_") {
      if (val == "clear")
        $("#" + i.substring(2)).hide();
      else
        $("#" + i.substring(2)).show();
    }
  });

  function ajustLastItem() {
    $last = $("#slide-out li").last();
    let margin = $(window).height() - $last.position().top - $last.children().outerHeight(true) + (($last.children().outerHeight(true) - $last.children().outerHeight()) / 2);
    if (margin >= 0) $last.css("margin-top", margin);
  }
});

function loadPage(page, titleNav, callback) {
  registerValues();

  if (titleNav) $("#titleNav").html(titleNav);
  if (page) {
    page = "html/" + page;
    if (page.substring(page.length - 5) != ".html") page += ".html";
    $("#mainRow").load(page, loadComplete);
  }

  function loadComplete() {
    registerValuesIfNot();

    $(".add").click(function () {
      modifyValue(this, +1);
    });

    $(".remove").click(function () {
      modifyValue(this, -1);
    });

    showValues();
    M.AutoInit();
    $("#loadPage").hide(); // or remove
    setTimeout(callback, 100);

    $.each($.cookie(), function (i, val) {
      if (i.substring(0, 2) == "c_") {
        $("#" + i).children().html(val);
      }
    });

    function modifyValue(that, num) {
      $input = $(that).parent().find("input");
      $input.val(parseInt($input.val()) + num);
    }
  }
}

function registerValues() {
  $.each($(".isvalue"), function (i, val) {
    switch (val.id.substring(0, 1)) {
      case "w":
        values[val.id] = $("#" + val.id).is(":checked");
        break;
      default:
        values[val.id] = $(val).val();
        break;
    }
  });
}

function registerValuesIfNot() {
  $.each($(".isvalue"), function (i, val) {
    if (!values[val.id]) {
      switch (val.id.substring(0, 1)) {
        case "w":
          values[val.id] = $("#" + val.id).is(":checked");
          break;
        default:
          values[val.id] = val.value;
          break;
      }
    }
  });
}

function showValues(specific) {
  if (!specific) specific = "";
  else specific += " "
  $.each($(specific + ".isvalue"), function (i, val) {
    if (values[val.id]) {
      switch (val.id.substring(0, 1)) {
        case "w":
          if (val.value) $("#" + val.id).attr("checked", true);
          break;
        case "s":
          val.value = values[val.id];
          if ($("#" + val.id).hasClass("withData")) {
            values[val.id] = $(val).val(); // Não sei pq, mas assim funciona (kappa)
            registerSelectLoad(val.id);
          }
          break;
        default:
          val.value = values[val.id];
          break;
      }
    }
  });
}

function saveConfig() {
  registerValues();
  let htmlString = "Salvo!<br/>" + addBrToJson(values);
  M.toast({ html: htmlString, classes: "rounded" });

  function addBrToJson(json) {
    let v = JSON.stringify(json, undefined, 4);
    let c = "";
    var s = "";
    let ident = 0;
    let marksClosed = true;
    for (let i = 0; i <= v.length; i++) {
      c = v.substring(i, i + 1);
      if (c == "\"") marksClosed = !marksClosed;
      if (marksClosed) {
        switch (c) {
          case "{":
            ident += 1;
            s += c + "<br/>" + getIdent();
            break;
          case "}":
            ident -= 1;
            s += "<br/>" + getIdent() + c;
            break;
          case ",":
            s += c + "<br/>" + getIdent();
            break;
          default:
            s += c;
            break;
        }
      } else {
        s += c;
      }
    }

    return s;

    function getIdent() {
      let r = "";
      for (let i = 0; i < ident; i++) {
        r += "&nbsp;&nbsp;&nbsp;&nbsp;";
      }
      return r
    }
  }
}

function changeSaveBtn(id) {
  $i = $("#" + id).children();
  if ($i.html() == "check") {
    $i.html("clear");
    $("#" + id.substring(2)).hide();
  } else {
    $i.html("check");
    $("#" + id.substring(2)).show();
  }

  $.cookie(id, $i.html());
}

function registerSelectLoad(id) {
  loadPageSelect(id);
  $("#" + id).on("change", function () {
    loadPageSelect(id);
  });
}

function loadPageSelect(id) {

  $selected = $("#" + id).find(":selected");
  let onpage = $("#" + id).data().onpage;
  let page = $selected.data().page;
  let callback = $selected.data().callback;
  if (page) $("#" + onpage).load("html/efeitosFitaL/" + page + ".html", loadComplete);

  function loadComplete() {
    window[callback]();
    showValues("#" + onpage);
  }
}

function estatico() {
  // load jsColor and implement onChage method
  loadJsColor().onChange = function (value) {
    let c = hexToRgb(value);
    $("#i_color_f1").val("rgb(" + c.r + "," + c.g + "," + c.b + ")");
  }
}

function hexToRgb(hex) {
  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}
