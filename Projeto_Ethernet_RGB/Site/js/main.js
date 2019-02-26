var valores = {};

$(document).ready(function () {
  ajustLastItem();
  loadPage("home", "Room Control");
  $("#d_ip").html("Host: " + window.location.host);

  $(window).resize(function () {
    ajustLastItem();
  });

  $("#slide-out li").click(function () {
    let va = setInterval(ajustLastItem, 0);
    setTimeout(function () { clearInterval(va); }, 500);
  });

  $.each($.cookie(), function (i, val) {
    if (i.substring(0, 3) == "c_b") {
      if (val == "clear")
        $("#" + i.substring(2)).hide();
      else
        $("#" + i.substring(2)).show();
    }
  });

  setInterval(kappa, 100);

  function kappa() {
    $('.sidenav-overlay').each(function () {

      $b = $("main, .fixed-action-btn");

      if ($(this).is(":visible") && !$b.hasClass("side-blur"))
        $b.addClass("side-blur");
      else if (!$(this).is(":visible") && $b.hasClass("side-blur"))
        $b.removeClass("side-blur");

    });
  }

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
    $("#mainRow").load(page, loadCompleted);
  }

  function loadCompleted() {
    loadComplete(false, callback);
  }
}

function loadComplete(showSpecific, callback) {
  registerValuesIfNot();

  $(".add").unbind('click').click(function () {
    modifyValue(this, +1);

    //if ($.cookie().c_s_saveImediato == "check") saveImmediately($(this).parent().find("input"));
  });

  $(".remove").unbind('click').click(function () {
    modifyValue(this, -1);

    //if ($.cookie().c_s_saveImediato == "check") saveImmediately($(this).parent().find("input"));
  });

  $("input[type=checkbox].isvalue.islighting").unbind('click').click(function () {
    let v = $.cookie().c_s_lightImediato;
    if (!v || v == "check") saveImmediately($(this));
  });

  if (showSpecific) showValues(showSpecific);
  else showValues();

  M.AutoInit();
  $("#loadPage").hide(); // or remove

  if (callback) setTimeout(callback, 100);

  $.each($.cookie(), function (i, val) {
    if (i.substring(0, 2) == "c_") {
      $("#" + i).children().html(val);
    }
  });

  function modifyValue(that, num) {
    $input = $(that).parent().find("input");
    $input.val(parseInt($input.val()) + num);
  }

  function saveImmediately(that) {
    let v = {};

    switch ($(that).get(0).id.substring(0, 1)) {
      case "w":
        v[$(that).get(0).id] = $(that).is(":checked");
        break;
      default:
        v[$(that).get(0).id] = $(that).get(0).value;
        break;
    }

    sendSave(v);
  }
}

function registerValues() {
  $.each($(".isvalue"), function (i, val) {
    switch (val.id.substring(0, 1)) {
      case "w":
        valores[val.id] = $("#" + val.id).is(":checked");
        break;
      default:
        valores[val.id] = val.value;
        break;
    }
  });
}

function registerValuesIfNot() {
  $.each($(".isvalue"), function (i, val) {
    if (!valores[val.id]) {
      switch (val.id.substring(0, 1)) {
        case "w":
          valores[val.id] = $("#" + val.id).is(":checked");
          break;
        default:
          valores[val.id] = val.value;
          break;
      }
    }
  });
}

function showValues(specific) {
  if (!specific) specific = "";
  else specific += " ";
  $.each($(specific + ".isvalue"), function (i, val) {
    if (valores[val.id]) {
      switch (val.id.substring(0, 1)) {
        case "w":
          if (val.value) $("#" + val.id).attr("checked", true);
          break;
        case "s":
          val.value = valores[val.id];
          if ($("#" + val.id).hasClass("withData")) {
            //valores[val.id] = $(val).val(); // Não sei pq, mas assim funciona (kappa)
            registerSelectLoad(val.id);
          }
          break;
        default:
          val.value = valores[val.id];
          break;
      }
    }
  });
}

function saveConfig() {
  registerValues();
  let htmlString = "Salvo!<br/>" + addBrToJson(valores);
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

function sendSave(itens) {

  let htmlString = "Salvo!<br/>" + addBrToJson(itens);
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
  registerValues();

  $item = $("#" + id);
  $selected = $item.find(":selected");
  let onpage = $item.data().onpage;
  let page = $selected.data().page;
  let callback = $selected.data().callback;
  if (page) $("#" + onpage).load("html/efeitosFitaL/" + page + ".html", loadCompleted);

  function loadCompleted() {
    if (callback) window[callback]();
    if ($item.hasClass("copy")) {
      $.each($("#" + onpage).find(".isvalue"), function (i, val) {
        val.id += "_f" + $item.data().copynumber;
      });
    }
    loadComplete("#" + onpage);
  }
}

function estatico() {
  // load jsColor and implement onChage method
  loadJsColor().onChange = function (element, value) {
    let c = hexToRgb(value);
    $(element).val("rgb(" + c.r + "," + c.g + "," + c.b + ")");
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
