var values = {};

$(document).ready(function () {
  ajustLastItem();
  loadPage("home", "Room Control", ajustLastItem);

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
        values[val.id] = val.value;
        break;
    }
  });
}

function showValues() {
  $.each($(".isvalue"), function (i, val) {
    if (values[val.id]) {
      switch (val.id.substring(0, 1)) {
        case "w":
          //$("#" + val.id).is(":checked");
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
    let ident = 0;
    for (let i = 0; i < v.length; i++) {
      if (v.substring(i, i + 1) == "{") {
        ident += 1;
        v = v.substring(0, i + 1) + "<br/>" + getIdent() + v.substring(i + 1);
        i += 5;
      } else if (v.substring(i, i + 1) == ",") {
        v = v.substring(0, i + 1) + "<br/>" + getIdent() + v.substring(i + 1);
        i += 5;
      } else if (v.substring(i, i + 1) == "}") {
        ident -= 1;
        v = v.substring(0, i) + "<br/>" + getIdent() + v.substring(i);
        i += 5;
      }
    }

    return v;

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